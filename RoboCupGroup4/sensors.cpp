//************************************
//         sensors.cpp       
//************************************

 // This file contains functions used to read and average
 // the sensors.


#include "sensors.h"
#include "Arduino.h"
#include "system.h"

const int proxy1 = 38;
// Local definitions
//#define 

// Read ultrasonic value
void read_ultrasonic(){
}

// Read infrared value
void read_infrared(){
  
}

// Read colour sensor value
void read_colour(){
}

// Pass in data and average the lot
void sensor_average(){

}


bool check_weight(){
  if (digitalRead(proxy1) == 0){
    return true;
  }
  return false;
}
