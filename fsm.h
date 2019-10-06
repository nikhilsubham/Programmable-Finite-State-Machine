
#ifndef __FSM__
#define __FSM__

#define MAX_INP_BUFFER_LEN  128
#define MAX_TRANSITION_TABLE_SIZE   128
#define MAX_STATE_NAME_SIZE 32
#define MAX_FSM_NAME_SIZE 32
#define MAX_TRANSITION_KEY_SIZE 64

typedef enum {

    FSM_FALSE,
    FSM_TRUE
} fsm_bool_t;


typedef struct state_ state_t;
typedef struct fsm_ fsm_t;

typedef struct tt_entry_ {

    char transition_key[MAX_TRANSITION_KEY_SIZE];
    unsigned int transition_key_size;
    state_t *next_state;
} tt_entry_t;

typedef struct tt_{

    tt_entry_t
        tt_entry[MAX_TRANSITION_TABLE_SIZE];
} tt_t;

struct state_ {

    /*Name of the state, must be unique within FSM*/
    char state_name[MAX_STATE_NAME_SIZE];
    /*Transition Table of the state*/
    tt_t state_trans_table;
    /*Boolean if the state is final or not*/
    fsm_bool_t is_final;
};

struct fsm_{

    /*Intitial state of FSM to start with*/
    state_t *initial_state;
    /*Name of FSM*/
    char fsm_name[MAX_FSM_NAME_SIZE];
    /* Application provided input data to parse
     * by FSM*/
    char input_buffer[MAX_INP_BUFFER_LEN];
    /* Length of above data*/
    unsigned int input_buffer_size;
    /*Cursor to read the above input_buffer in coninuation*/
    unsigned int input_buffer_cursor;
};

#define FSM_ITERATE_TRANS_TABLE_BEGIN(tr_table_ptr, tt_entry_ptr)   \
    do{                                                             \
        unsigned int index = 0;                                     \
        for(; index < MAX_TRANSITION_TABLE_SIZE; index++){          \
            tt_entry_ptr = &(tr_table_ptr->tt_entry[index]);        \
            if(is_tt_entry_empty(tt_entry_ptr) == FSM_TRUE)         \
            break;                                                  \


#define FSM_ITERATE_TRANS_TABLE_END(tr_table_ptr, tt_entry_ptr)     \
        }}while(0);

typedef enum {

        FSM_NO_TRANSITION,
        FSM_NO_ERROR
} fsm_error_t;


#endif
