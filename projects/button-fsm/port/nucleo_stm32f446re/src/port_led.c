#include "port_led.h"
#include "port_system.h"

#define MODER5_MASK (0x03 << 5 * 2) /* Cada pin ocupa 2 bits */
#define PUPDR5_MASK (0x03 << 5 * 2) /* Cada pin ocupa 2 bits */

#define MODER5_AS_OUTPUT (GPIO_MODE_OUT << 5 * 2)     /* Cada pin ocupa 2 bits */
#define PUPDR5_AS_NOPUPD (GPIO_PUPDR_NOPULL << 5 * 2) /* Cada pin ocupa 2 bits */

#define IDR5_MASK (0x01 << 5) /* Cada pin ocupa 1 bit */
#define ODR5_MASK (0x01 << 5) /* Cada pin ocupa 1 bit */

/* **TO-DO alumnos: ** implement port_led_gpio_setup */

/* **TO-DO alumnos: ** implement port_led_toggle */
