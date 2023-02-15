#ifndef FSM_H_
#define FSM_H_

#include <stdbool.h>

typedef struct fsm_t fsm_t;

/// @brief alias for the input condition function of a Finite State Machine (FSM).
typedef bool (*fsm_input_func_t)(fsm_t *);

/// @brief alias for the output modification function of a Finite State Machine (FSM).
typedef void (*fsm_output_func_t)(fsm_t *);

/// @brief transition of a Finite State Machine (FSM).
typedef struct fsm_trans_t
{
    int orig_state;        //!< origin state.
    fsm_input_func_t in;   //!< input condition function.
    int dest_state;        //!< destination state.
    fsm_output_func_t out; //!< output modification function.
} fsm_trans_t;

/// @brief struct to define a Finite State Machine (FSM).
struct fsm_t
{
    int current_state; //!< current state of the FSM.
    fsm_trans_t *p_tt; //!< pointer to the state transition table.
};

/**
 * @brief allocates memory on the heap and returns a pointer to a new Finite State Machine (FSM).
 *
 * @note the initial state of the FSM corresponds to the origin state of the first transition of the table
 * @note the table must end with a null transition {-1, NULL, -1, NULL}. This is how the library detects the end of the table.
 * @note this function allocates memory in the heap. Once you are done with the FSM, you must call fsm_destroy to free the memory.
 *
 * @param p_tt ppointer to the transition table associated to the FSM.
 * @return fsm_t* pointer to the new FSM.
 */
fsm_t *fsm_new(fsm_trans_t *p_tt);

/**
 * @brief Configures the initial state of a provided Finite State Machine (FSM) according to its transition table.
 *
 * @note the initial state of the FSM corresponds to the origin state of the first transition of the table
 * @note the table must end with a null transition {-1, NULL, -1, NULL}. This is how the library detects the end of the table.
 *
 * @param p_fsm pointer to the FSM being initialized.
 * @param p_tt ppointer to the transition table associated to the FSM.
 */
void fsm_init(fsm_t *p_fsm, fsm_trans_t *p_tt);

/**
 * @brief it reads the transition table of a Finite State Machine (FSM) and, if any input condition is met,
 * it moves to a new state and executes the corresponding output modification function
 *
 * @param p_fsm pointer to the FSM.
 */
void fsm_fire(fsm_t *p_fsm);

/**
 * @brief Frees the memory allocated in the heap for a given Finite State Machine (FSM).
 *
 * @note Once called this function, the FSM cannot be used again.
 * @note You only need to call this function if the FSM was created using fsm_new.
 *
 * @param p_fsm pointer to the FSM being destroyed.
 */
void fsm_destroy(fsm_t *p_fsm);

#endif /* FSM_H_ */
