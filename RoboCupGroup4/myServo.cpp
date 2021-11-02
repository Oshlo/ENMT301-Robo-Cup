//************************************
//         myServo.cpp
//************************************
#include "Arduino.h"
#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "myServo.h"
#include <Servo.h>

Task tServo(TASK_MILLISECOND * 30, TASK_FOREVER, &myservo_callback);


static int servo_left_pin = 5;
static int servo_right_pin = 4;
bool isServoActivated = false;


Servo myservo_left;      // create servo object to control a servo
Servo myservo_right; 

int dest_pos = 0;
int outval = 180;
int inval = 10;
int pos = inval;

int velocity;





void set_servo_velocity(int percentage){
    if (percentage <= 100 && percentage >= 0) {
    int velocity = 0;
    velocity = map(percentage, 0, 100, TASK_MILLISECOND * 50, TASK_MILLISECOND * 1);
    tServo.setInterval(velocity);
  }
}

void move_servo(int value){
  int val1;
  int val2;
  val1 = map(value, 0, 200, 10, 180);  // scale it to use it with the servo (value between 500 and 2500) 
  val2 = map(value, 200, 0, 5, 175);
  myservo_left.write(val1);      // sets the servo position according to the scaled value 
  myservo_right.write(val2); 
}

bool is_servo_out(){
  if (pos==outval){
    return true;
  }
  return false;
}

bool is_servo_in(){
  if (pos == inval){
    return true;
  }
  return false;
}

void servo_out(){
  dest_pos = outval;
}

void servo_in(){
  dest_pos = inval;
}

bool is_servo_activated(){
  return isServoActivated;
}


void myservo_callback(){
  if (dest_pos == pos){
    tServo.disable();
  }else{
    if ((dest_pos - pos)>0){
      pos+=1;
    }else{
      pos-=1;
    }
    move_servo(pos);
  }
}

bool servo_enable_callback(){
  isServoActivated = true;
  return true;
}

void servo_disable_callback(){
  isServoActivated = false;
}


void myservo_init(){
  myservo_left.attach(servo_left_pin);  // attaches the servo  to the servo object
  myservo_right.attach(servo_right_pin);  // attaches the servo  to the servo object
  move_servo(pos);
  tServo.setOnEnable(&servo_enable_callback);
  tServo.setOnDisable(&servo_disable_callback);
}
