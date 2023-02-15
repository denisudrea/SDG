#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_led.h"
#include "port_system.h"

#define T_LED_MS 1000 // Period of the LED

/**
 * @brief main routine
 *
 *  * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Initialize the system \n
 * > ✅ 2. Initialize the LED GPIO \n
 * > ✅ 3. Infinite loop that toggles the LED value. The toggling period must be T_LED_MS \n
 * > ✅ 4. Even thought it never returns, it is good practice to return 0 at the end of the function.
 *
 * @return this function never returns.
 */
int main(){
    port_system_init () ;
    port_led_gpio_setup () ;
    while (1) {
        port_led_toggle () ;
        port_system_delay_ms ( T_LED_MS / 2) ;
    }
    return 0;
}