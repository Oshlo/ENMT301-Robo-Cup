#define IR A11 // Left

float rawValue = 0;
float mapped = 0;
float x = 0;

float alpha = 0.01;    //initialization of EMA alpha
float lowPass1 = 0;
float lowPass2 = 0;
float lowPass3 = 0;

double coeffs1[] = {-0.0000929212, 0.04400735, -7.0960892, 410.80288};
double coeffs2[] = {0.0003137413, -0.2557757, 51.691856};

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  lowPass1 = analogRead(IR);
  lowPass2 = analogRead(IR);
  lowPass3 = analogRead(IR);
}

void loop() {
  rawValue = analogRead(IR);
  Serial.print(rawValue); Serial.print(",");
  lowPass1 = (alpha*rawValue) + ((1-alpha)*lowPass1);
  lowPass2 = (alpha*lowPass1) + ((1-alpha)*lowPass2);
  lowPass3 = (alpha*lowPass2) + ((1-alpha)*lowPass3);
  x = lowPass3;
  Serial.println(x);
  

  if (x <= 190) {
    mapped = (coeffs1[0]*pow(x, 3)) + (coeffs1[1]*pow(x, 2)) + (coeffs1[2]*x) + (coeffs1[3]);
  } else if (x > 190 && x <= 370) {
    mapped = (coeffs2[0]*pow(x, 2)) + (coeffs2[1]*x) + (coeffs2[2]);
  } else {
    mapped = 0;
  }
  delay(5);
}
