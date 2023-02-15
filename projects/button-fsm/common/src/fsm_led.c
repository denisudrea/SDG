#include <stddef.h>
#include <stdlib.h>
#include "fsm_button.h"
#include "fsm_led.h"
#include "port_led.h"
#include "port_system.h"

typedef struct
{
    /* **TO-DO alumnos:** add all the fields required for this FSM */
} fsm_led_t;

/**
 * @brief checks if the latest button duration is long enough to toggle the LED
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to LED FSM \n
 * > ✅ 2. Get button's latest duration using p_button \n
 * > ✅ 3. Check if it is greater than min_duration
 *
 * @param p_fsm pointer to the LED FSM.
 * @return true if the latest button duration is long enough.
 */
static bool check_button_duration(fsm_t *p_fsm)
{
    return false;
}

/**
 * @brief toggles the board LED and resets the latest button duration measurement
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to LED FSM \n
 * > ✅ 2. Reset button's latest duration using p_button \n
 * > ✅ 3. Toggle the board LED.
 *
 * @param p_fsm pointer to the LED FSM.
 */
static void do_toggle(fsm_t *p_fsm)
{
}

/**
 * @brief LED FSM state enumeration
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Define the FSM's states.
 *
 */
enum FSM_LED_STATES
{
};

/**
 * @brief LED FSM transition table
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Define the FSM's transitions. \n
 * > ✅ 2. Add a null transition (this is mandatory for all the FSMs).
 *
 */
static fsm_trans_t fsm_trans_led[] = {
};

fsm_t *fsm_led_new(fsm_t *p_button, uint32_t min_duration)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_led_t));
    if (p_fsm)
    {
        fsm_led_init(p_fsm, p_button, min_duration);
    }
    return p_fsm;
}

void fsm_led_init(fsm_t *p_fsm, fsm_t *p_button, uint32_t min_duration)
{
    fsm_led_t *p_led = (fsm_led_t *) p_fsm;
    fsm_init(&p_led->fsm, fsm_trans_led);
    /* **TO-DO alumnos: complete this function ** */
}
