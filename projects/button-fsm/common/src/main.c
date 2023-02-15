#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "fsm_led.h"
#include "fsm_button.h"

#define T_DEBOUNCE_MS 200 // Button debounce time
#define MIN_DURATION_MS 1000 // Minimum button duration time
#define T_FSM_MS 10   // Trigger period of the FSM

/**
 * @brief main routine
 *
 *  * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Initialize the system \n
 * > ✅ 2. Create new FSMs \n
 * > ✅ 3. Infinite loop that triggers the FSMs periodically \n
 * > ✅ 4. Clean up memory and return 0 (not necessary, this is just good practices)
 *
 * @return this function never returns.
 */
int main() {
    return 0;
}
