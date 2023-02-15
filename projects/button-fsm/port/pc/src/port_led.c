#include "port_led.h"

void port_led_gpio_setup() {}

/**
 * @brief Board toggle led
 *
 */
void port_led_toggle()
{
    static bool led_status = false;
    if (!led_status)
    {
        led_status = true;
        printf("[%lld] LED ON\n", (long long)port_system_get_millis());
    }
    else 
    {
        led_status = false;
        printf("[%lld] LED OFF\n", (long long)port_system_get_millis());
    }
    fflush(stdout); // Force output
}
