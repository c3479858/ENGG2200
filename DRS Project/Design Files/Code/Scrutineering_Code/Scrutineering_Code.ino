#include <PWMServo.h>
#define ledPin 13
#define servoPin 19

PWMServo drs;

int openAngle = 0;
int closedAngle = 30;

//const int ledPin = 13;

void setup() {
  //manual servo set up to avoid 0-90-0 sweep
  analogWriteFrequency(servoPin, 67);       // 67Hz servo frequency (teehee)
  analogWrite(servoPin, 0);                 // NO MOVE THE SERVO
  delay(100);

  //drs.attach(19, 544, 2400);         // attach with pulse range
  drs.attach(servoPin);                     //servo attach
  drs.write(closedAngle);            

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  drs.write(openAngle);
  digitalWrite(ledPin, HIGH);
  Serial.println("Wing open");
  delay(5000);
  drs.write(closedAngle);
  digitalWrite(ledPin, LOW);
  Serial.println("Wing closed");
  delay(5000);
}