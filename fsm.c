#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

fsm_t *create_new_fsm(const char *fsm_name){

    fsm_t * fsm = calloc(1, sizeof(fsm_t));
    strncpy(fsm->fsm_name, fsm_name, MAX_FSM_NAME_SIZE - 1);
    fsm->fsm_name[MAX_FSM_NAME_SIZE - 1] = '\0';
    return fsm;
}

void
set_fsm_initial_state(fsm_t *fsm, state_t *state){
    
    assert(!fsm->initial_state);
    fsm->initial_state = state;
}

void
set_fsm_input_buffer_size(fsm_t *fsm, unsigned int size){

    fsm->input_buffer[size] = '\0';
    fsm->input_buffer_size = size;
}


state_t *
create_new_state(fsm_t *fsm, char *state_name,
                 fsm_bool_t is_final){

    assert(state_name);
    
    state_t *state = calloc(1, sizeof(state_t));
    
    strncpy(state->state_name, state_name, MAX_STATE_NAME_SIZE -1);
    state->state_name[MAX_STATE_NAME_SIZE -1] = '\0';

    state->is_final = is_final;
    return state;
}

static fsm_bool_t
is_tt_entry_empty (tt_entry_t *tt_entry){

    if(!tt_entry->next_state){
        return FSM_TRUE;
    }

    return FSM_FALSE;
}

static tt_entry_t *
get_next_empty_tt_entry(tt_t *trans_table){

    tt_entry_t *tt_entry_ptr = NULL;
    
    assert(trans_table);

    /*Helping looping macros to iterate over non-empty 
     * transition entries of transition table*/
    FSM_ITERATE_TRANS_TABLE_BEGIN(trans_table, tt_entry_ptr){
        /*No Op*/
    } FSM_ITERATE_TRANS_TABLE_END(trans_table, tt_entry_ptr);

    if(is_tt_entry_empty(tt_entry_ptr) == FSM_TRUE)
        return tt_entry_ptr;

    return NULL;
}


void create_and_insert_new_tt_entry(tt_t *trans_table,
        char *transition_key,
        unsigned int sizeof_key,
        state_t *next_state){

    assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);

    tt_entry_t *tt_entry_ptr = get_next_empty_tt_entry(trans_table);
    
    if(!tt_entry_ptr){
        printf("FATAL : Transition Table is Full\n");
        return;
    }

    memcpy(tt_entry_ptr->transition_key, transition_key, sizeof_key);
    tt_entry_ptr->transition_key[sizeof_key] = '\0';
    tt_entry_ptr->transition_key_size = sizeof_key;
    tt_entry_ptr->next_state = next_state;
}


fsm_error_t
execute_fsm(fsm_t *fsm, 
            char *input_buffer,         /*Input buffer containing user data*/
            unsigned int size,          /*Size of the data in the buffer*/
            fsm_bool_t *fsm_result){    /*A flag to track if data parsing ends in final state or not */


}

