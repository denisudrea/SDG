/**
 ******************************************************************************
 * @file           : port_system.h
 * @brief          : Header for port_system.c file.
 ******************************************************************************
 * @attention
 *
 * Josue Pagán Ortiz (j.pagan@upm.es)
 * Sistemas Digitales II
 *
 ******************************************************************************
 */

#ifndef PORT_SYSTEM_H_
#define PORT_SYSTEM_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* HW dependent includes */
#include "stm32f4xx.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BIT_POS_TO_MASK(x) (0x01 << x)  /*!< Convert the index of a bit into a mask by left shifting */
#define BASE_MASK_TO_POS(m, p) (m << p) /*!< Move a mask defined in the LSBs to upper positions by shifting left p bits */

/* Microcontroller STM32F446RE */
/* Timer configuration */
#define RCC_HSI_CALIBRATION_DEFAULT 0x10U            /*!< Default HSI calibration trimming value */
#define TICK_FREQ_1KHZ 1U                            /*!< Freqency in kHz of the System tick */
#define NVIC_PRIORITY_GROUP_0 ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority, \
                                                         4 bits for subpriority */
#define NVIC_PRIORITY_GROUP_4 ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority, \
                                                         0 bit  for subpriority */

/* Power */
#define POWER_REGULATOR_VOLTAGE_SCALE3 0x01 /*!< Scale 3 mode: the maximum value of fHCLK is 120 MHz. */

/* GPIOs */
#define HIGH true /*!< Logic 1 */
#define LOW false /*!< Logic 0 */

#define GPIO_MODE_IN 0x00        /*!< GPIO as input */
#define GPIO_MODE_OUT 0x01       /*!< GPIO as output */
#define GPIO_MODE_ALTERNATE 0x02 /*!< GPIO as alternate function */
#define GPIO_MODE_ANALOG 0x03    /*!< GPIO as analog */

#define GPIO_PUPDR_NOPULL 0x00 /*!< GPIO no pull up or down */
#define GPIO_PUPDR_PUP 0x01    /*!< GPIO no pull up */
#define GPIO_PUPDR_PDOWN 0x02  /*!< GPIO no pull down */

/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief  This function is based on the initialization of the HAL Library; it must be the first
 *         thing to be executed in the main program (before to call any other
 *          functions), it performs the following:
 *           - Configure the Flash prefetch, instruction and Data caches.
 *           - Configures the SysTick to generate an interrupt each 1 millisecond, which is clocked by the HSI (at this stage, the clock is not yet configured and thus the system is running from the internal HSI at 16 MHz).
 *           - Set NVIC Group Priority to 4.
 *             NVIC_PRIORITYGROUP_4: 4 bits for preemption priority
 *                                    0 bits for subpriority
 *           - Configure the system clock
 *
 * @note   SysTick is used as time base for the delay functions. When using the HAL, the application
 *         needs to ensure that the SysTick time base is always set to 1 millisecond
 *         to have correct HAL operation.
 *    When the NVIC_PRIORITYGROUP_0 is selected, IRQ preemption is no more possible.
 *         The pending IRQ priority will be managed only by the subpriority.
 * @retval Init status
 */
size_t port_system_init(void);

/**
 * @brief Get the count of the System tick in milliseconds
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Return System tick \n
 *
 * @return uint32_t
 */
uint32_t port_system_get_millis(void);

/**
 * @brief Wait for some milliseconds
 *
 * @param ms Number of milliseconds to wait
 *
 * @retval None
 */
void port_system_delay_ms(uint32_t ms);

/**
 * @brief Wait for some milliseconds from a time reference.
 *
 * @note It also updates the time reference to the system time at return.
 *
 * @param p_t Pointer to the time reference
 * @param ms Number of milliseconds to wait
 *
 * @retval None
 */
void port_system_delay_until_ms(uint32_t *p_t, uint32_t ms);

#endif /* PORT_SYSTEM_H_ */
