//************************************
//         system.h    
//************************************

#ifndef SYSTEM_H_
#define SYSTEM_H_

//define state machine
enum{STATE_INIT, STATE_AUTO, STATE_MANUAL, NUM_STATE};
//define substates
enum{STATE_AUTO_MOVING, STATE_WEIGHT_IN_PLACE, STATE_WEIGHT_FOUND, STATE_TURN, NUM_SUBSTATE};

void set_state(int state);
int get_state();

void set_substate(int substate);
int get_substate();

unsigned long get_time();
unsigned long duration(unsigned long time_stamp);

void system_callback();
#endif
