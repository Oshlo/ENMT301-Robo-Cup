#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "test.h"
#include "longRangeIR.h"
#include "midRangeIR.h"
#include "motors.h"
#include "Arduino.h"



Task tTest(100000, -1, &TestCallback);
Task tSensorValue(100*TASK_MILLISECOND, -1, &sensorCallback);

extern Task tLongIRR;
extern Task tLongIRL;
extern Task tMidIRR;
extern Task tMidIRL;

float midValR = 0;
float midValL = 0;
float longValR = 0;
float longValL = 0;

int state = 0;

void TestCallback(void) {
  midValR = getMidRangeIRR();
  midValL = getMidRangeIRL();
  longValR = getLongRangeIRR();
  longValL = getLongRangeIRL();

  

  if ((abs(longValR - longValL) < 30)) {
    if ((longValR - midValR) > 20) {
      //Serial.println("Difference between top right and bottom right sensors less than 30.");
      if (midValR < 40) {
        //Serial.println("Bottom right sensor detecting weight.");
        // stop state
        state = 0;
      } else {
        // spin state
        state = 1;
      }
    } else if ((longValL - midValL) > 20) {
      //Serial.println("Difference between top left sensor and bottom left sensors greater than 30.");
      if (midValL < 40) {
        //Serial.println("Bottom left sensor detecting weight.");
        // stop state
        state = 0;
      } else {
        // spin state
        state = 1;
      }
    } else {
      // spin state
      state = 1;
    }
  } else {
    //Serial.println("Difference between top right and left sensors greater than 30");
    // spin state
    state = 1;
  }


  switch (state) {
    case 0:
      Serial.println("Stop State");
      //set_motor(MOTOR_LEFT, MOTOR_FORWARD, 0);
      //set_motor(MOTOR_RIGHT, MOTOR_FORWARD, 0);
      break;
    case 1:
    Serial.println("Spin state");
      //set_motor(MOTOR_LEFT, MOTOR_FORWARD, 60);
      //set_motor(MOTOR_RIGHT, MOTOR_REVERSE, 60);
      break;
  }
}


void sensorCallback() {
  Serial.print(getMidRangeIRR()); Serial.print(",");
  Serial.print(getMidRangeIRL()); Serial.print(",");
  Serial.print(getLongRangeIRR()); Serial.print(",");
  Serial.println(getLongRangeIRL());
}







/*
float val = 0;
float er = 0;
float maxError = 0;
float actual = 70;
int testCount = 0;
float testSum = 0;
float testAverage = 0;
*/

/*
void TestCallback(void) {  
  val = getMidRangeIRR();
  er = abs(val - actual);
  testSum += er;
  
  if (er > maxError) {
    maxError = er;
  }
  
  if (testCount == 200) {
    testAverage = testSum/testCount;
    Serial.print("Error Average: "); Serial.println(testAverage);
    Serial.print("Error Maximum: "); Serial.println(maxError);
    Serial.println("Reset");
    maxError = 0;
    testCount = 0;
    er = 0;
    testSum = 0;
  } else {
    testCount++;
  }
}
*/
