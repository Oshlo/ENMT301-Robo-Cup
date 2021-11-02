#define _TASK_MICRO_RES
#include <TaskSchedulerDeclarations.h>
#include "ultrasonic.h"
#include "Arduino.h"

Task tUltrasonic(500*TASK_MILLISECOND, -1, &ultrasonicTaskCallback);

int distance = 0;
int duration[WINDOW_SIZE];
int avgDuration = 0;
int prevDistance = 0;
int sum = 0;
int count = 0;

void ultrasonicTaskCallback() {
  prevDistance = distance;
  distance = getDistance();
}

int getDuration() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int pulse = pulseIn(echoPin, HIGH);
  return pulse > 0 ? pulse: 0;
}

int getDistance() {
  for (int i = 0; i < WINDOW_SIZE; i++) {
    duration[i] = getDuration();
    sum += duration[i];
  }
  avgDuration = sum/WINDOW_SIZE;
  distance = avgDuration * 0.0172;
  sum = 0;
  if (distance < 0) {
    distance = prevDistance;
  } else if ((distance - prevDistance) > 10) {
    count++;
    if (count == 5) {
      count = 0;
    } else {
      distance = prevDistance;
    }
  }
  Serial.println(distance);
  return distance;
}

int returnDistance() {
  return distance;
}

void ultrasonic_init(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
