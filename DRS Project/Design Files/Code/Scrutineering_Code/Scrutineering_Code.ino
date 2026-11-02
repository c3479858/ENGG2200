#include <PWMServo.h>

PWMServo drs;

int openAngle = 30;
int closedAngle = 0;

const int ledPin = 13;

void setup() {
  // Manually set up PWM at servo frequency BEFORE attaching
  analogWriteFrequency(19, 50);       // 50Hz servo frequency
  analogWrite(19, 0);                 // no pulse — servo holds position
  delay(100);

  drs.attach(19, 544, 2400);         // attach with pulse range
  drs.write(closedAngle);            // first real command is your desired angle

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  drs.write(openAngle);
  digitalWrite(ledPin, HIGH);
  delay(2500);
  drs.write(closedAngle);
  digitalWrite(ledPin, LOW);
  delay(2500);
}