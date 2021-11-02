/********************************************************************************
                                 ROBOCUP GROUP4
                                 Hank Wu
                                 Georgia Reynolds
                                 Adam Finlayson
 ******************************************************************************/
#define _TASK_MICRO_RES
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>

#include <Adafruit_TCS34725.h>      //colour sensor
#include <Wire.h>                   //for I2C and SPI

// Custom headers
#include "motors.h"
#include "sensors.h"
#include "weight_collection.h"
#include "ps2controller.h"
#include "system.h"
#include "myStepper.h"
#include "ultrasonic.h"

#include "longRangeIR.h"
#include "midRangeIR.h"

#include "captureSys.h"
#include "myServo.h"


//**********************************************************************************
// Local Definitions
//**********************************************************************************

// Pin deffinitions
#define IO_POWER  49

// Serial deffinitions
#define BAUD_RATE 9600

//**********************************************************************************
// Task Scheduler and Tasks
//**********************************************************************************
Scheduler taskManager;

extern Task tbutton_logic;
extern Task tStepper;
extern Task tSystem;
extern Task tStepper_calibration;
extern Task tUltrasonic;


extern Task tLongIRR;
extern Task tLongIRL;
extern Task tMidIRR;
extern Task tMidIRL;
extern Task tTest;
extern Task tSensorValue;


extern Task tCapture;
extern Task tServo;


//**********************************************************************************
// Function Definitions
//**********************************************************************************
void pin_init();
void robot_init();
void task_init();


//**********************************************************************************
// put your setup code here, to run once:
//**********************************************************************************
void setup() {
  Serial.begin(BAUD_RATE);
  pin_init();
  robot_init();
  task_init();
  Wire.begin();
}

//**********************************************************************************
// Initialise the pins as inputs and outputs (otherwise, they won't work)
// Set as high or low
//**********************************************************************************
void pin_init() {
  //Serial.println("Pins have been initialised \n");
  pinMode(IO_POWER, OUTPUT);              //Pin 49 is used to enable IO power
  digitalWrite(IO_POWER, 1);              //Enable IO power on main CPU board
  motor_init();
  stepper_init();
  ps2_init();
  ultrasonic_init();

  longRangeIR_init();
  midRangeIR_init();

  captureSys_init();
  myservo_init();

}

//**********************************************************************************
// Set default robot state
//**********************************************************************************
void robot_init() {
  //Serial.println("Robot is ready");
}

//**********************************************************************************
// Initialise the tasks for the scheduler
//**********************************************************************************
void task_init() {

  // This is a class/library function. Initialise the task scheduler
  taskManager.init();

  // Add tasks to the scheduler
  taskManager.addTask(tStepper);
  taskManager.addTask(tSystem);
  taskManager.addTask(tCapture);
  taskManager.addTask(tServo);
  taskManager.addTask(tStepper_calibration);
  taskManager.addTask(tbutton_logic);
  taskManager.addTask(tUltrasonic);

  taskManager.addTask(tLongIRR);
  taskManager.addTask(tLongIRL);
  taskManager.addTask(tMidIRR);
  taskManager.addTask(tMidIRL);
  taskManager.addTask(tTest);
  taskManager.addTask(tSensorValue);

  //enable the tasks. ONLY system should be enable in the first place.
  //other task please enabled in the system.
  tSystem.enableIfNot();
  //tUltrasonic.enableIfNot();
  tLongIRR.enableIfNot();
  tLongIRL.enableIfNot();
  tMidIRL.enableIfNot();
  tMidIRR.enableIfNot();
  tSensorValue.enableIfNot();
  //tTest.enableIfNot();
  Serial.println("System started");
}



//**********************************************************************************
// Main loop
//**********************************************************************************
void loop() {
  taskManager.execute();
}
