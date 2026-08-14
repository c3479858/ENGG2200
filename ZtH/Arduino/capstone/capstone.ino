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
#define ledPin 13  //internal LED is pin 13
#define buttonPin 2
#define analogPin A0
#define redLed 9     //9 is a pwm pin
#define greenLed 10  //10 is a pwm pin
#define blueLed 11   //11 is a pwm pin

//Initialising values
unsigned long timeNow = 0;
unsigned long timeLast = 0;

const float bitRef = 1023.0;  //reference for maximum read value of A0 (2^10)

//hertz, this is used to determine report rate of Serial and flash rate of LED simultaneously. These can be decoupled but that is out of scope
const int hertz = 5;

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

  //NOTE unsure whether to initialise these in the preamble or not, both seem to function the same
  int buttonState = digitalRead(buttonPin);
  int analogState = analogRead(analogPin);
  int analogPercent = ((analogState / bitRef) * 100);  //changes analogState from 2^10 to an integer percentage

  if ((timeNow - timeLast) >= 500 / hertz) {    //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                         //resets loop
    analogWrite(ledPin, !digitalRead(ledPin));  //sets led to whatever state it isn't in

    //Serial printing
    //NOTE: unsure how to condense this, maybe something similar to python .format
    Serial.print("Button is ");
    Serial.println(buttonState);
    Serial.print("Potentiometer is at ");
    Serial.print(analogPercent);
    Serial.println("%");
  }

  if (buttonState == 0) {                     //when button is pressed (i.e. 0)
    rgbControl(14, 117, 184, analogPercent);  //change to one of the specified colour if needed
  } else {
    rgbControl(0, 0, 0, 0);  //switch LED off
  }                          //rgbControl call is probably more efficient than manually setting analogWrite for all pins.
}


//rgbControl function, sets led to a specified value and brightness, where i is an integer percentage!!
void rgbControl(int r, int g, int b, int i) {
  analogWrite(redLed, (i / 100.0) * r);
  analogWrite(greenLed, (i / 100.0) * g);
  analogWrite(blueLed, (i / 100.0) * b);
}