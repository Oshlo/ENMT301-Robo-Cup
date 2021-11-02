//************************************
//         ps2controller.h    
//************************************
#include "motors.h"
#include "myStepper.h"
#include "ps2controller.h"
#include "Arduino.h"
#include <PS2X_lib.h>
#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

Task tbutton_logic(TASK_MILLISECOND * 300, TASK_FOREVER, &button_logic_callback);

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;

bool button_status[BUT_NUM];

void ps2_init() {
  error = ps2x.config_gamepad(45, 43, 44, 42, true, true);
}


void button_logic_callback() {
  int val1 = 0;
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  if (ps2x.NewButtonState()) {
    if(ps2x.ButtonPressed(PSB_TRIANGLE)){
      stepper_move_to_A();
    }else if(ps2x.ButtonPressed(PSB_CIRCLE)){
      stepper_move_to_B();
    }else if(ps2x.ButtonPressed(PSB_CROSS)){
      stepper_move_to_C();
    }else if (ps2x.ButtonPressed(PSB_R1)){
      mag_on();
    }else if (ps2x.ButtonPressed(PSB_R2)){
      mag_off();
    }
  }
}


void serial_control_callback(){
  int num = 0;
  num = Serial.parseInt();
  set_stepper_step(num);
}
