#include <PS2X_lib.h>
#include <Servo.h>
PS2X ps2x;

//right now, the library does NOT support hot-pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
int val1;
int val2;
byte type = 0;
byte vibrate = 0;
int IRdistance1;
int IRdistance2;

Servo myservoA;      // create servo object to control a servo
Servo myservoB;      // create servo object to control a servo
Servo myservoC;
Servo myservoD;


void setup() {
  Serial.begin(57600);


  error = ps2x.config_gamepad(45, 43, 44, 42, true, true); //GamePad(clock, command, attention, data, Pressures?, Rumble?


  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  myservoA.attach(3);  // attaches the servo pin 3 to the servo object
  myservoB.attach(2);  // attaches the servo pin 2 to the servo object
  myservoC.attach(4);
  myservoC.write(90);
  myservoD.attach(5);

}

void loop() {
  /* You must Read Gamepad to get new values
    Read GamePad and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values

    you should call this at least once a second
  */

  if (error == 1)
    return;
  else { //DualShock Controller

    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.NewButtonState()) {
      if (ps2x.Button(PSB_PAD_UP)) {        //will be TRUE as long as button is pressed
        myservoA.writeMicroseconds(1800);
        myservoB.writeMicroseconds(1800);
      }else if (ps2x.Button(PSB_PAD_RIGHT)) {
        myservoA.writeMicroseconds(1800);
        myservoB.writeMicroseconds(1200);
      }else if (ps2x.Button(PSB_PAD_LEFT)) {
        myservoA.writeMicroseconds(1200);
        myservoB.writeMicroseconds(1800);
      }else if (ps2x.Button(PSB_PAD_DOWN)) {
        myservoA.writeMicroseconds(1200);
        myservoB.writeMicroseconds(1200);
      }else{
        myservoA.writeMicroseconds(1500);
        myservoB.writeMicroseconds(1500);
      }
    }

  }

  IRdistance1 = analogRead(A0);
  IRdistance2 = analogRead(A1);

  Serial.print(IRdistance1);
  Serial.print("\t");
  Serial.println(IRdistance2);
  
  val1 = ps2x.Analog(PSS_LY);
  val2 = ps2x.Analog(PSS_LX);
  val1 = map(val1, 0, 255, 0, 180);  // scale it to use it with the servo (value between 500 and 2500)
  val2 = map(val2, 0, 255, 0, 180);
  myservoC.write(val1);      // sets the servo position according to the scaled value


  delay(50);

}
