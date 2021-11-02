//************************************
//         myStepper.h    
//************************************
#ifndef MY_STEPPER_H_
#define MY_STEPPER_H_

void stepper_motor_callback(void);
void set_stepper_step(int steps);
void set_stepper_stop();
int get_stepper_step();
void set_stepper_speed(int percentage);
void stepper_calibrate();
bool is_stepper_calibrated();
bool is_stepper_activate();
void stepper_init();
void stepper_run(void);
void stepper_calibrate();
void stepper_move_to_A();
void stepper_move_to_B();
void stepper_move_to_C();
void stepper_move_to_D();
void mag_on();
void mag_off();

void stepper_motor_callback();
#endif
