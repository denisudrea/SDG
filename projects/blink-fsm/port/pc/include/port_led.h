#ifndef PORT_BLINK_H_
#define PORT_BLINK_H_

/* Includes del sistema */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Includes del sistema */
#include "port_system.h"

void port_led_gpio_setup(void);
void port_led_toggle(void);

#endif
