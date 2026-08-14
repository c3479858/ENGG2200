/*
ENGG2200 Arduino Zero to Hero Capstone Project
Author: Theo Devos-Vernes
Student Number: c3479858
Last Modified: 14 August, 2026

Description:
Reports sign of life by pulsing onboard LED at specified rate (5Hz)
Reports button and potentiometer states via Serial at 9600 Baud at specified rate (5Hz)
Illuminates external LED with specified colour when the button is pressed
Allowing brightness modulation based on the position of the potentiometer
*/

//Pin assignments
#define ledPin 13
#define buttonPin 2
#define analogPin A0
#define redLed 9
#define greenLed 10
#define blueLed 11

unsigned long timeNow = 0;
unsigned long timeLast = 0;
int buttonState = 0;
int analogState = 0;
int analogPercent = 0;
const int hertz = 5;
const float bitRef = 1023.0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(analogPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  timeNow = millis();  //sets timeNow to current millis
  buttonState = digitalRead(buttonPin);
  analogState = analogRead(analogPin);
  analogPercent = ((analogState / bitRef) * 100);  //changes analogState from 2^10 to a percentage

  if ((timeNow - timeLast) >= 1000 / hertz) {  //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                        //resets loop
    digitalWrite(ledPin, !digitalRead(ledPin));      //sets led to whatever state it isn't in (in theory)

    Serial.print("Button is ");
    Serial.println(buttonState);
    Serial.print("Potentiometer is at ");
    Serial.print(analogState);
    Serial.println("%");
  }
  if (buttonState = HIGH) {
    rgbControl(14, 117, 184, analogPercent);  //change to one of the specified colour if needed
  } else {
    rgbControl(0, 0, 0, 0);
  }
}

void rgbControl(int r, int g, int b, int i) {
  digitalWrite(redLed, (i / 100.0) * r);
  digitalWrite(greenLed, (i / 100.0) * g);
  digitalWrite(blueLed, (i / 100.0) * b);
}

/* not good use of functions, relocated to loop()

void pulse(led, button, pot, hertz) {
  timeNow = millis();  //sets timeNow to current millis

  if ((timeNow - timeLast) >= 1000 / hertz) {  //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                        //resets loop
    digitalWrite(led, !digitalRead(led));      //sets led to whatever state it isn't in (in theory)

    buttonState = digitalRead(button);
    analogState = analogRead(pot);
    analogPercent = ((analogState / bitRef) * 100);

    Serial.print("Button is ");
    Serial.println(buttonState);
    Serial.print("Potentiometer is at ");
    Serial.print(analogState);
    Serial.println("%");
  }
}
*/