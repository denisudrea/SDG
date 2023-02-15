#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "fsm_blink.h"

#define T_LED_MS 1000 // Period of the LED blink
#define T_FSM_MS 10   // Trigger period of the FSM

/**
 * @brief main routine
 *
 *  * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Initialize the system \n
 * > ✅ 2. Create new blink FSM \n
 * > ✅ 3. Infinite loop that triggers the FSM periodically \n
 * > ✅ 4. Clean up memory and return 0 (not necessary, this is just good practices)
 *
 * @return this function never returns.
 */
 int main () {
 port_system_init () ;
 fsm_t * p_fsm = fsm_blink_new ( T_LED_MS ) ;
 uint32_t t = port_system_get_millis () ;
 while (1)
 {
 fsm_fire ( p_fsm );
 port_system_delay_until_ms (&t, T_FSM_MS );
 }
 fsm_destroy ( p_fsm ) ;
return 0;
}
