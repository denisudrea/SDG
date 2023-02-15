#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

#include <stdbool.h>

/**
 * @brief configures the GPIO pin of the button.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Enable GPIOC clock in AHB1ENR \n
 * > ✅ 2. Clean previous configuration for pin 13 in MODER and PUPDR \n
 * > ✅ 2. Set pin 13 mode as input in MODER \n
 * > ✅ 3. Set pull up/down configuration as no PUPD for pin 13 in PUPDR
 *
 */
void port_button_gpio_setup(void);

/**
 * @brief reads status of the button and returns true if it is pressed.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Read button value in the corresponding IDR register \n
 *
 * @return true if button is pressed, false otherwise
 */
bool port_button_read(void);

#endif // PORT_BUTTON_H_
