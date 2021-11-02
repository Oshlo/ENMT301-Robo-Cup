


//************************************
//         system.cpp
//************************************


#include <PS2X_lib.h>
#include "Arduino.h"
#include "ps2controller.h"
#include "system.h"
#include "myStepper.h"
#include "motors.h"

#include "longRangeIR.h"
#include "midRangeIR.h"

#include "sensors.h"
#include "captureSys.h"
#include "myServo.h"

#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

Task tSystem(TASK_MILLISECOND * 50, TASK_FOREVER, &system_callback);

extern Task tStepper;
extern Task tStepper_calibration;

extern Task tLongIRR;
extern Task tLongIRL;
extern Task tMidIRL;

extern Task tbutton_logic;
extern Task tCapture;
extern Task tServo;


static int State = 0;
static int Substate = 0;



void update_state() {

}

void set_state(int state) {
  if (state < NUM_STATE) {
    State = state;
  }
}


int get_state() {
  return State;
}

void set_substate(int substate) {

}

int get_substate() {
  return Substate;
}


unsigned long get_time() {
  return micros();
}


unsigned long duration(unsigned long time_stamp) {
  unsigned long now = 0;
  unsigned long diff = 0;
  now = micros();
  //if (now < time_stamp){  //overflow case
  //  diff = time_stamp - now;
  // diff = 4294967295 - diff;
  //}else{                  //normal case
  diff = now - time_stamp;
  //}

  return diff;
}


void system_callback() {
  static int stage = 0;
  
  // conditial execution task
  if (get_stepper_step() != 0 && is_stepper_activate() == false) {
    tStepper.restartDelayed();
  }
  //sequential execution task
  if (State == STATE_INIT) {
    switch (stage) {
      case 0:
        tStepper_calibration.enableIfNot();
        stage++;
        break;
      case 1:
        if (is_stepper_calibrated()) {
          stage++;
        }
        break;
      case 2:
        stage++;
        break;
      case 3:
        //tbutton_logic.enableIfNot();
        State = STATE_AUTO;
        stage++;
        break;
    }
  }


  if (State == STATE_AUTO) {
    if (!is_capture_activated() && read_left_proximity()){
      set_motor(MOTOR_LEFT, MOTOR_FORWARD, 100);
      set_motor(MOTOR_RIGHT, MOTOR_FORWARD, 100);
      tCapture.enableIfNot();
    }
  }
}
