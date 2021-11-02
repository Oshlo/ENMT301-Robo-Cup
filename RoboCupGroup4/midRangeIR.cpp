#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "midRangeIR.h"
#include "Arduino.h"



Task tMidIRR(50000, -1, &midRangeIRRCallback);
Task tMidIRL(50000, -1, &midRangeIRLCallback);

float midRawR = 0;
float midRawL = 0;

float midxR = 0;
float midxL = 0;

float midMappedR = 0;
float midMappedL = 0;

float midAlpha = 0.3;

float midFirstPassR = 0;
float midFirstPassL = 0;
float midSecondPassR = 0;
float midSecondPassL = 0;

double midCoeffsR1[] = {0.0013277, -0.7523844, 117.89913};
double midCoeffsR2[] = {0.00046509, -0.372954, 74.85715};
double midCoeffsL1[] = {-0.0000929212, 0.04400735, -7.0960892, 410.80288};
double midCoeffsL2[] = {0.0003137413, -0.2557757, 51.691856};

void midRangeIR_init() {
  midFirstPassR = analogRead(MidIRR);
  midSecondPassR = analogRead(MidIRR);
  midFirstPassL = analogRead(MidIRL);
  midSecondPassL = analogRead(MidIRL);
}

void midRangeIRRCallback() {
  midRawR = analogRead(MidIRR);
  midFirstPassR = (midAlpha*midRawR) + ((1-midAlpha)*midFirstPassR);
  midSecondPassR = (midAlpha*midFirstPassR) + ((1-midAlpha)*midSecondPassR);

  midxR = midSecondPassR;
  if (midxR <= 255) {
    midMappedR = (midCoeffsR1[0]*pow(midxR, 2)) + (midCoeffsR1[1]*midxR) + (midCoeffsR1[2]);
  } else if (midxR > 255 && midxR <= 390) {
    midMappedR = (midCoeffsR2[0]*pow(midxR, 2)) + (midCoeffsR2[1]*midxR) + (midCoeffsR2[2]);
  } else {
    midMappedR = 0;
  }
}

void midRangeIRLCallback() {
  midRawL = analogRead(MidIRL);
  midFirstPassL = (midAlpha*midRawL) + ((1-midAlpha)*midFirstPassL);
  midSecondPassL = (midAlpha*midFirstPassL) + ((1-midAlpha)*midSecondPassL);

  midxL = midSecondPassL;
  if (midxL <= 190) {
    midMappedL = (midCoeffsL1[0]*pow(midxL, 3)) + (midCoeffsL1[1]*pow(midxL, 2)) + (midCoeffsL1[2]*midxL) + (midCoeffsL1[3]);
  } else if (midxL > 190 && midxL <= 370) {
    midMappedL = (midCoeffsL2[0]*pow(midxL, 2)) + (midCoeffsL2[1]*midxL) + (midCoeffsL2[2]);
  } else {
    midMappedL = 0;
  }
}

float getMidRangeIRR() {
  return midMappedR;
}

float getMidRangeIRL() {
  return midMappedL; 
}

float getMidRawR() {
  return midRawR;
}
