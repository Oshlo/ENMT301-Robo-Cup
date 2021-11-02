//************************************
//         motors.cpp
//************************************

#include "motors.h"
#include "Arduino.h"
#include "system.h"
#include <Servo.h>

Servo right_motor;
Servo left_motor;



/* In this section, the motor speeds should be updated/written.
  It is also a good idea to check whether value to write is valid.
  It is also a good idea to do so atomically!
  Useing port S1 and channels S1 and S2 to drive the two motors on the robot.
  The motors must be connected through the Sabertooth driver.
  The sabertooth must be in mode Microcontroller pulses, independent linear control mode.
  1000us to 2000us control the speed and direction. 1500us is stop.
  Any speed outside this range will be ignored.
*/



void set_motor(int motor, int dir, int motor_speed_percentage) {
  int motor_speed = 0;
  if (motor_speed_percentage <= 100 && motor_speed_percentage >= 0) {

    if (dir == MOTOR_FORWARD)
      motor_speed = map(motor_speed_percentage, 0, 100, 1500, 2000);
    else if (dir == MOTOR_REVERSE)
      motor_speed = map(motor_speed_percentage, 0, 100, 1500, 1000);
    else
      motor_speed = 1500;

    if (motor == MOTOR_LEFT)
      left_motor.writeMicroseconds(motor_speed);
    else if (motor == MOTOR_RIGHT)
      right_motor.writeMicroseconds(motor_speed);
  }
}





void motor_init() {
  //initialise drive motor
  right_motor.attach(3);
  left_motor.attach(2);
}
