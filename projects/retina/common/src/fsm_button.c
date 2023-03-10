/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_button.h"
#include "port_button.h"

/* Typedefs --------------------------------------------------------------------*/
typedef struct
{
    fsm_t f;                    /*!< Button FSM */
    uint32_t debounce_time;     /*!< Button debounce time in ms */
    uint32_t next_timeout;      /*!< Next timeout for the anti-debounce in ms */
    uint32_t tick_pressed;      /*!< Number of ticks when the button was pressed */
    uint32_t duration;          /*!< How much time the button has been pressed */
    uint32_t button_id;         /*!< Button ID. Must be unique */
} fsm_button_t;

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
enum  	FSM_BUTTON {
  BUTTON_RELEASED = 0,      /*!< Starting sate. Alseo comes here when button has been released */
  BUTTON_RELEASED_WAIT,     /*!< State to perform the anti-debounce mechanism for a falling edge */
  BUTTON_PRESSED,           /*!< State while the button is being pressed */
  BUTTON_PRESSED_WAIT       /*!< State to perform the ante-debounce mechansim for a rising edge */
};
/* State machine input or transition functions */


/* State machine output or action functions */


/* Other auxiliary functions */


fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);

    /* TO-DO alumnos: */
}

static bool check_button_pressed (fsm_t *p_this){
    return (port_button_is_pressed(p_this));
}

static bool check_button_released	(fsm_t *p_this)	{
    return !(check_button_pressed(p_this));
}

static bool check_timeout (fsm_t *p_this){
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    if(port_button_get_thick() > p_fsm->next_timeout){
        return true;
    }else return false;
}	

static void do_store_tick_pressed	(fsm_t *p_this){
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    p_fsm->tick_pressed = port_button_get_thick();
    p_fsm->next_timeout = p_fsm->tick_pressed + p_fsm->debounce_time;


}

/* State machine input or transition functions */
static void do_set_duration	(fsm_t *p_this)	{
    int now=port_button_get_thick();
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    p_fsm->duration = now - p_fsm->tick_pressed;
    p_fsm->next_timeout = now + p_fsm->debounce_time;
}
