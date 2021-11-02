#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "longRangeIR.h"
#include "Arduino.h"



Task tLongIRR(50000, -1, &longRangeIRRCallback);
Task tLongIRL(50000, -1, &longRangeIRLCallback);

float rawR = 0;
float rawL = 0;

float xR = 0;
float xL = 0;

float mappedR = 0;
float mappedL = 0;

float alpha = 0.3;

float firstPassR = 0;
float firstPassL = 0;
float secondPassR = 0;
float secondPassL = 0;

double coeffsR[] = {8.3557E-9, -1.342E-5, 0.0078831, -2.1118796191142, 257.4441315098428};
double coeffsL[] = {1.17347E-8, -1.648183E-5, 8.456623E-3, -1.985785, 221.670756};

void longRangeIR_init() {
  firstPassR = analogRead(LongIRR);
  secondPassR = analogRead(LongIRR);
  firstPassL = analogRead(LongIRL);
  secondPassL = analogRead(LongIRL);
}

void longRangeIRRCallback() {
  rawR = analogRead(LongIRR);
  firstPassR = (alpha*rawR) + ((1-alpha)*firstPassR);
  secondPassR = (alpha*firstPassR) + ((1-alpha)*secondPassR);

  xR = secondPassR;
  if (xR < 66) {
    mappedR = 150;
  } else {
    mappedR = (coeffsR[0]*pow(xR, 4)) + (coeffsR[1]*pow(xR, 3)) + (coeffsR[2]*pow(xR, 2)) + (coeffsR[3]*xR) + (coeffsR[4]);
  }
}

void longRangeIRLCallback() {
  rawL = analogRead(LongIRL);
  firstPassL = (alpha*rawL) + ((1-alpha)*firstPassL);
  secondPassL = (alpha*firstPassL) + ((1-alpha)*secondPassL);

  xL = secondPassL;
  if (xL < 46) {
    mappedL = 150;
  } else {
    mappedL = (coeffsL[0]*pow(xL, 4)) + (coeffsL[1]*pow(xL, 3)) + (coeffsL[2]*pow(xL, 2)) + (coeffsL[3]*xL) + (coeffsL[4]);
  }
}

float getLongRangeIRR() {
  return mappedR;
}

float getLongRangeIRL() {
  return mappedL; 
}
