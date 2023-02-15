#include "port_button.h"
#include "port_system.h"

#define MODER13_MASK (0x03 << 13 * 2) /* Cada pin ocupa 2 bits */
#define PUDR13_MASK (0x03 << 13 * 2)  /* Cada pin ocupa 2 bits */

#define MODER13_AS_INPUT (GPIO_MODE_IN << 13 * 2)       /* Cada pin ocupa 2 bits */
#define PUPDR13_AS_NOPUPD (GPIO_PUPDR_NOPULL << 13 * 2) /* Cada pin ocupa 2 bits */

#define IDR13_MASK (0x01 << 13) /* Cada pin ocupa 1 bit */

/* **TO-DO alumnos: ** implement port_button_gpio_setup */

/* **TO-DO alumnos: ** implement port_button_read */
