//************************************
//         captureSys.cpp
//************************************
#include "Arduino.h"
#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "captureSys.h"
#include "myStepper.h"
#include "myServo.h"

Task tCapture(TASK_MILLISECOND * 50, TASK_FOREVER, &capture_callback);
extern Task tServo;

bool isCaptureActivate = false;

static int weight_status = STANDING_UP;
static int proximity_right_pin = 35;
static int proximity_left_pin = 34;



void set_weight_status(int num) {
  weight_status = num;
}

bool read_left_proximity(void) {
  return (!digitalRead(proximity_left_pin));
}


void captureSys_init(void) {
  pinMode(proximity_right_pin, INPUT);
  pinMode(proximity_left_pin, INPUT);
}


bool is_capture_activated() {
  return isCaptureActivate;
}

void capture_callback(void) {
  static int stage = 0;
  static int counter = 0;
  switch (stage) {
    case 0://start the capture sequence if the stepper is not activate.
      if (is_stepper_activate() == false) {
        isCaptureActivate = true;
        stage++;
      }
      break;

    case 1://move stepper to upright position
      stepper_move_to_B();
      stage++;
      break;

    case 2://wait the stepper to activate
      if (is_stepper_activate()) {
        stage++;
      }
      break;

    case 3://wait the stepper to reach the position
      if (is_stepper_activate() == false) {
        stage++;
      }
      break;

    case 4: //turn on electro magnet.
      mag_on();
      stage++;
      break;

    case 5: //move to drop position
      stepper_move_to_D();
      stage++;
      break;

    case 6: //wait the stepper to activate
      if (is_stepper_activate()) {
        stage++;
      }
      break;

    case 7: //wait the spepper to reach the position and initiate servo.
      if (is_stepper_activate() == false) {
        servo_out();
        set_servo_velocity(100);
        tServo.enableIfNot();
        stage++;
      }
      break;

    case 8:
      if (is_servo_out()) {
        stage++;
      }
      break;

    case 9:
      if (counter < 5) {
        counter++;
      } else {
        counter = 0;
        mag_off();
        stage++;
      }
      break;

    case 10:
      if (counter < 5) {
        counter++;
      } else {
        counter = 0;
        servo_in();
        set_servo_velocity(80);
        tServo.enableIfNot();
        stage++;
      }
      break;

    case 11://reset
      if (is_servo_in()) {
        stepper_move_to_A();
        stage++;
      }
      break;

    case 12: //wait the stepper to activate
      if (is_stepper_activate()) {
        stage++;
      }
      break;

    case 13: //wait the spepper to reach the position
      if (is_stepper_activate() == false) {
        isCaptureActivate = false;
        tCapture.disable();
        stage = 0;
      }
      break;
  }
}
