#include "port_led.h"
#include "port_system.h"

#define MODER5_MASK (0x03 << 5 * 2) /* Cada pin ocupa 2 bits */
#define PUPDR5_MASK (0x03 << 5 * 2) /* Cada pin ocupa 2 bits */

#define MODER5_AS_OUTPUT (GPIO_MODE_OUT << 5 * 2) /* Cada pin ocupa 2 bits */
#define PUPDR5_AS_NOPUPD (GPIO_PUPDR_NOPULL << 5 * 2) /* Cada pin ocupa 2 bits */

#define IDR5_MASK (0x01 << 5) /* Cada pin ocupa 1 bit */
#define ODR5_MASK (0x01 << 5) /* Cada pin ocupa 1 bit */

/* **TO-DO alumnos: ** implement port_led_gpio_setup */
void port_led_gpio_setup ()
{
/* Primero , habilitamos siempre el reloj de los perifericos */
RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN ;
/* Luego , limpiamos los registros MODER y PUPDR c o r r e s p o n d i e n t e s */
GPIOA -> MODER &= ~ MODER5_MASK ;
GPIOA -> PUPDR &= ~ PUPDR5_MASK ;
/* Finalmente , configuramos el LED como salida sin pull up/ pull down */
GPIOA -> MODER |= MODER5_AS_OUTPUT ;
GPIOA -> PUPDR |= PUPDR5_AS_NOPUPD ;
}
/* **TO-DO alumnos: ** implement port_led_toggle */
void port_led_toggle ()
 {
 /* Leemos el valor previo del LED en IDR */
 uint32_t prev_value = (GPIOA -> IDR & IDR5_MASK );
 /* Segun corresponda , apagamos o encendemos el LED en ODR */
 if ( prev_value )
 {
 GPIOA -> ODR &= ~ ODR5_MASK ; /* Apagar : escribimos un 0 logico */
 }
 else
 {
GPIOA -> ODR |= ODR5_MASK ; /* Encender : escribimos un 1 logico */
  }
}