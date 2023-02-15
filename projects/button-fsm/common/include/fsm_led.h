#ifndef FSM_LED_H_
#define FSM_LED_H_

#include <stdint.h>
#include "fsm.h"

/**
 * @brief Creates a new FSM for blinking the LED of the board according to button pulses.
 *
 * @note this function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_destroy to free memory.
 *
 * @param p_button pointer to button FSM. It is necessary to read the duration measurements.
 * @param min_duration minimum duration (in ms) of a button pulse to toggle the LED.
 *
 * @return fsm_t* pointer to the LED FSM.
 */
fsm_t * fsm_led_new(fsm_t *p_button, uint32_t min_duration);

/**
 * @brief Initializes all the parameters for an FSM that blinks the LED of the board.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to LED FSM (we already provide this) \n
 * > ✅ 2. Initialize its inner FSM (we already provide this) \n
 * > ✅ 3. Fill all the fields of the LED FSM to their initial value \n
 * > ✅ 4. Configure the GPIO of the LED accordingly.
 *
 * @param p_fsm pointer to the FSM.
 * @param p_button pointer to button FSM. It is necessary to read the duration measurements.
 * @param min_duration minimum duration (in ms) of a button pulse to toggle the LED.
 */
void fsm_led_init(fsm_t *p_fsm, fsm_t *p_button, uint32_t min_duration);

#endif // FSM_LED_H_
