//************************************
//         myStepper.cpp
//************************************
#include "Arduino.h"
#include "myStepper.h"
#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>

Task tStepper(400, 2, &stepper_motor_callback);
Task tStepper_calibration(TASK_MILLISECOND * 50, TASK_FOREVER, &stepper_calibrate);


const int stepPin = 31;
const int dirPin = 30;
const int swPin = 33;
const int elemagPin = 32;

static int Stepper_steps = 0;
static int Stepper_speed = 400;


static int Stepper_posA = -2000;
static int Stepper_posB = -2792;
static int Stepper_posC = -4450;
static int Stepper_posD = 45;

static int Stepper_pos = 0;
static bool Stepper_active = false;
static bool Stepper_calibrating = false;
static bool Stepper_calibrated = false;

static bool stepper_motor_step() {
  static bool first = true;
  static bool sFlag = false;
  if (first) {
    digitalWrite(stepPin, HIGH);
    first = false;
  } else if (first == false) {
    digitalWrite(stepPin, LOW);
    sFlag = true;
    first = true;
  }

  if (sFlag) {
    sFlag = false;
    return true;
  } else {
    return false;
  }
}




void stepper_run(void)
{ static int mystep = 0;
  if (Stepper_calibrating == true) {
    if (digitalRead(swPin)) {
      set_stepper_stop();
    }
  }

  if (Stepper_steps > 0) {
    digitalWrite(dirPin, HIGH);
    mystep = stepper_motor_step();
    Stepper_steps -= mystep;
    Stepper_pos += mystep;
  } else if (Stepper_steps < 0) {
    digitalWrite(dirPin, LOW);
    mystep = stepper_motor_step();
    Stepper_steps += mystep;
    Stepper_pos -= mystep;
  }
}


//rest position
void stepper_move_to_A() {
  Stepper_steps =  Stepper_posA - Stepper_pos;
}

//upright position
void stepper_move_to_B() {
  Stepper_steps =  Stepper_posB - Stepper_pos;
}

//knocked off position
void stepper_move_to_C() {
  Stepper_steps =  Stepper_posC - Stepper_pos;
}

//drop weight position
void stepper_move_to_D() {
  Stepper_steps =  Stepper_posD - Stepper_pos;
}


void stepper_calibrate() {
  static int stage = 0;
  static bool sw_pushed = false;
  switch (stage) {
    case 0:
      if (Stepper_calibrated == false) {
        stage++;
      }
      break;
      
    case 1:
      if (digitalRead(swPin)) {
        set_stepper_step(-500);
        set_stepper_speed(100);
        stage++;
      } else {
        Stepper_calibrating = true;
        stage = 4;
      }
      break;
      
    case 2:
      if (is_stepper_activate()) {
        stage++;
      }
      break;
      
    case 3:
      if (is_stepper_activate() == false) {
        Stepper_calibrating = true;
        stage++;
      }
      break;
      
    case 4:
      set_stepper_step(10000);
      stage++;
      break;
      
    case 5:
      if (is_stepper_activate() || digitalRead(swPin)) {
        stage++;
      }
      break;
    case 6:
      if (is_stepper_activate() == false) {
        Stepper_pos = 0;
        Stepper_calibrating = false;
        Stepper_calibrated = true;
        stepper_move_to_A();
        tStepper_calibration.disable();
        stage = 0;
      }
      break;
  }
}


void stepper_init() {
  //initialise stepper motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(elemagPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  pinMode(swPin, INPUT);
}

void set_stepper_step(int steps) {
  Stepper_steps += steps;
}


void set_stepper_stop() {
  Stepper_steps = 0;
}

int get_stepper_step() {
  return Stepper_steps;
}

void set_stepper_speed(int percentage) {
  if (percentage <= 100 && percentage >= 0) {
    Stepper_speed = map(percentage, 0, 100, 10000, 400);
    tStepper.setInterval(Stepper_speed);
  }
}


int get_stepper_speed() {
  return Stepper_speed;
}

bool is_stepper_activate() {
  return Stepper_active;
}


bool is_stepper_calibrated() {
  return Stepper_calibrated;
}


void stepper_motor_callback() {
  static int count = 0;
  count++;
  stepper_run();
  if (count == 2) {
    count = 0;
    if (get_stepper_step() != 0) {
      tStepper.restartDelayed (get_stepper_speed());
      Stepper_active = true;
    } else {
      Stepper_active = false;
    }
  }
}



static void stepper_zero() {
  Stepper_pos = 0;
}

void mag_on() {
  digitalWrite(elemagPin, HIGH);
}

void mag_off() {
  digitalWrite(elemagPin, LOW);
}
