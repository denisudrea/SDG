/**
 * @file port_system.c
 * @brief File that defines the functions that are related to the access to the specific HW of the microcontroller.
 * @author Sistemas Digitales II
 * @date 2023-01-01
 */

/* Includes ------------------------------------------------------------------*/
#include "port_system.h"

/* Defines -------------------------------------------------------------------*/
#define HSI_VALUE ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz */
#define EXTIx 0x0F  //
#define TRIGGER_RISING_EDGE 0x01  //Constante flanco de subida
#define TRIGGER_FALLING_EDGE 0x02 //Constante flanco de bajada
//#define TRIGGER_BOTH_EDGE  0x03 //Constante flanco de subida y bajada
#define EVENT_REQUEST 0x04  //
#define INTERRUPT_REQUEST 0x08  //








/* GLOBAL VARIABLES */
static uint32_t msTicks = 0; /*!< Variable to store millisecond ticks. @warning **It must be declared volatile!** Just because it is modified in an ISR. **Add it to the definition** after *static*. */

/* These variables are declared extern in CMSIS (system_stm32f4xx.h) */
uint32_t SystemCoreClock = HSI_VALUE; /*!< Frequency of the System clock */
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9}; /*!< Prescaler values for AHB bus */
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4}; /*!< Prescaler values for APB bus */

//------------------------------------------------------
// SYSTEM CONFIGURATION
//------------------------------------------------------
/**
 * @brief  Setup the microcontroller system
 *         Initialize the FPU setting, vector table location and External memory
 *         configuration.
 *
 * @note   This function is called at startup by CMSIS in startup_stm32f446xx.s.
 */
void SystemInit(void)
{
/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#endif                                                 /* USER_VECT_TAB_ADDRESS */
}

/**
 * @brief System Clock Configuration
 *
 * @attention This function should NOT be accesible from the outside to avoid configuration problems.
 * @note This function starts a system timer that generates a SysTick every 1 ms.
 * @retval None
 */
static void system_clock_config(void)
{
  /** Configure the main internal regulator output voltage */
  /* Power controller (PWR) */
  /* Control the main internal voltage regulator output voltage to achieve a trade-off between performance and power consumption when the device does not operate at the maximum frequency */
  PWR->CR &= ~PWR_CR_VOS; // Clean and set value
  PWR->CR |= (PWR_CR_VOS & (POWER_REGULATOR_VOLTAGE_SCALE3 << PWR_CR_VOS_Pos));

  /* Initializes the RCC Oscillators. */
  /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
  RCC->CR &= ~RCC_CR_HSITRIM; // Clean and set value
  RCC->CR |= (RCC_CR_HSITRIM & (RCC_HSI_CALIBRATION_DEFAULT << RCC_CR_HSITRIM_Pos));

  /* RCC Clock Config */
  /* Initializes the CPU, AHB and APB buses clocks */
  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
      must be correctly programmed according to the frequency of the CPU clock
      (HCLK) and the supply voltage of the device. */

  /* Increasing the number of wait states because of higher CPU frequency */
  FLASH->ACR = FLASH_ACR_LATENCY_2WS; /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */

  /* Change in clock source is performed in 16 clock cycles after writing to CFGR */
  RCC->CFGR &= ~RCC_CFGR_SW; // Clean and set value
  RCC->CFGR |= (RCC_CFGR_SW & (RCC_CFGR_SW_HSI << RCC_CFGR_SW_Pos));

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HSI_VALUE >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];

  /* Configure the source of time base considering new system clocks settings */
  SysTick_Config(SystemCoreClock / (1000U / TICK_FREQ_1KHZ)); /* Set Systick to 1 ms */
}

size_t port_system_init()
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  /* Configure Flash prefetch, Instruction cache, Data cache */
  /* Instruction cache enable */
  FLASH->ACR |= FLASH_ACR_ICEN;

  /* Data cache enable */
  FLASH->ACR |= FLASH_ACR_DCEN;

  /* Prefetch cache enable */
  FLASH->ACR |= FLASH_ACR_PRFTEN;

  /* Set Interrupt Group Priority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

  /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  /* Configure the SysTick IRQ priority. It must be the highest (lower number: 0)*/
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0U, 0U)); /* Tick interrupt priority */

  /* Init the low level hardware */
  /* Reset and clock control (RCC) */
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* Syscfg clock enabling */

  /* Peripheral clock enable register */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN; /* PWREN: Power interface clock enable */

  /* Configure the system clock */
  system_clock_config();

  return 0;
}

//------------------------------------------------------
// TIMER RELATED FUNCTIONS
//------------------------------------------------------
uint32_t port_system_get_millis()
{
  return msTicks;
}

void port_system_delay_ms(uint32_t ms)
{
  uint32_t tickstart = port_system_get_millis();

  while ((port_system_get_millis() - tickstart) < ms)
  {
  }
}

void port_system_delay_until_ms(uint32_t *p_t, uint32_t ms)
{
  uint32_t until = *p_t + ms;
  uint32_t now = port_system_get_millis();
  if (until > now)
  {
    port_system_delay_ms(until - now);
  }
  *p_t = port_system_get_millis();
}

//------------------------------------------------------
// GPIO RELATED FUNCTIONS
//------------------------------------------------------
void port_system_gpio_config(GPIO_TypeDef * port, uint8_t pin, uint8_t mode, uint8_t pupd) 
{
  if(port == GPIOA){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  }
  else if (port == GPIOB){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  }
  else if (port == GPIOC){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  }
  
}

void port_system_gpio_config_exti(GPIO_TypeDef * p_port, uint8_t pin, uint32_t mode)
{
  RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  int i;  
  
  

  if (pin >= 0 && pin <= 3) {
    i = 0;
  } else if (pin >= 4 && pin <= 7) {
    i = 1;
  } else if (pin >= 8 && pin <= 11) {
    i = 2;
  } else if (pin >= 12 && pin <= 15) {
    i = 3;
  }

  //Borrado del registro del puerto
  SYSCFG -> EXTICR[i] &= ~(EXTIx << 4*(pin % 4));

  //Asociaci??n de interrupci??n externa a puerto
  if (p_port == GPIOA){
    SYSCFG -> EXTICR[i] |= (0 << 4*(pin % 4));
  } else if (p_port == GPIOB){
    SYSCFG -> EXTICR[i] |= (1 << 4*(pin % 4));
  } else if (p_port == GPIOC){
    SYSCFG -> EXTICR[i] |= (2 << 4*(pin % 4));
  }

//Seleci??n de modo de disparo: flanco de subida, bajada, ambos.
  if (mode && TRIGGER_RISING_EDGE){EXTI->RTSR |= BIT_POS_TO_MASK(pin);}
  if (mode && TRIGGER_FALLING_EDGE){EXTI->FTSR |= BIT_POS_TO_MASK(pin);}

//Selecci??n de modo: petici??n de evento o petici??n de interrupci??n 
  if(mode && EVENT_REQUEST){EXTI->EMR |= BIT_POS_TO_MASK(pin);}
  if(mode && INTERRUPT_REQUEST){EXTI->IMR |= BIT_POS_TO_MASK(pin);}
}

//Funci??n ya definida
void port_system_gpio_exti_enable(uint8_t pin, uint8_t priority, uint8_t subpriority)
{
  NVIC_SetPriority(GET_PIN_IRQN(pin), NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority, subpriority));
  NVIC_EnableIRQ(GET_PIN_IRQN(pin));
}

//Funci??n ya definida
void port_system_gpio_exti_disable(uint8_t pin)
{  
  NVIC_DisableIRQ(GET_PIN_IRQN(pin));
}

//Funci??n que lee el valor digital de un pin (0 o 1) == (true o false) 
bool port_system_gpio_read(GPIO_TypeDef * p_port, uint8_t pin){
  bool value = (bool)(p_port -> IDR & BIT_POS_TO_MASK(pin));
  return value;
}

//Funci??n que llamaremos cuadno queramos dar valor a un pin digital (1 o 0)
void port_system_gpio_write(GPIO_TypeDef * 	p_port, uint8_t 	pin, bool 	value){
  if (value) {
        // set the pin
        p_port->BSRR = (uint32_t) (1 << pin);
    } else {
        // clear the pin
        p_port->BSRR = (uint32_t) (1 << (pin + 16));
    }
  }

  //Fucni??n que lee el valor de un pin y escribe el valor opuesto. Usa las macros HIGH y LOW
  void port_system_gpio_toggle(GPIO_TypeDef *p_port, uint8_t pin) {
    if (p_port->IDR & BIT_POS_TO_MASK(pin)) {
        p_port->BSRR = (uint32_t) (LOW << (pin + 16));
    } else {
        p_port->BSRR = (uint32_t) (HIGH << pin);
    }
}
//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief This function handles the System tick timer that increments the system millisecond counter (global variable).
 * 
 * > **TO-DO alumnos:**
 * >
 * > ??? 1. **Increment the System tick counter `msTicks` in 1 count.** \n
 * > &nbsp;&nbsp;&nbsp;&nbsp;???? `msTicks` is a global `static` variable declared in @link port_system.c @endlink. \n
 *
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified in this ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition)
. **Add it to the definition** after *static*.
 *
 */
void SysTick_Handler(void)
{
  /* TO-DO alumnos */   
  msTicks++; 
}
