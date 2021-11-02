#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define  trigPin    38
#define  echoPin    39
#define WINDOW_SIZE 2

void ultrasonicTaskCallback();
int getDuration();
int getDistance();
int returnDistance();
void ultrasonic_init();

#endif /* ULTRASONIC_H_ */
