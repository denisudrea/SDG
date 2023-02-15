#ifndef FSM_BLINK_H_
#define FSM_BLINK_H_

#include <stdint.h>
#include "fsm.h"

/**
 * @brief Creates a new FSM for blinking the LED of the board.
 * 
 * @note this function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_destroy to free memory.
 *
 * @param period_ms period (in ms) of the LED blink.
 *
 * @return fsm_t* pointer to the LED FSM.
 */
fsm_t * fsm_blink_new(uint32_t period_ms);

/**
 * @brief Initializes all the parameters for an FSM that blinks the LED of the board.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to blink FSM (we already provide this) \n
 * > ✅ 2. Initialize its inner FSM (we already provide this) \n
 * > ✅ 3. Fill all the fields of the blink FSM to their initial value \n
 * > ✅ 4. Configure the GPIO of the LED accordingly.
 *
 * @param p_fsm pointer to the FSM.
 * @param period_ms blinking period of the LED.
 */
void fsm_blink_init(fsm_t *p_fsm, uint32_t period_ms);

#endif // FSM_BLINK_H_
