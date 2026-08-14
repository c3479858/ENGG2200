//Code for reading a button and potentiometer and outputting result to Serial

#define buttonPin 2  //button pin, change if needed
#define analogPin A0

const int hertz = 5;
//const float voltageRef = 5.0;     //voltage reference
const float bitRef = 1023.0;  //reference bit for 100%, change to 1024 if needed

int timeNow = 0;
int timeLast = 0;

int buttonState = 0;
int analogState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  //enables built in pullup resistor so button functions as expected
  pinMode(analogPin, INPUT);         //sets A0 to be an input (for potentiometer)
}

void loop() {
  buttonState = digitalRead(buttonPin);                //sets button state
  analogState = analogRead(analogPin);                 //sets analog state for potentiometer
  int analogPercent = ((analogState / bitRef) * 100);  //gives analog reading as a percentage
  timeNow = millis();                                  //sets timeNow to current millis

  if ((timeNow - timeLast) >= (500) / hertz) {  //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                         //resets loop
    Serial.println(buttonState);                //prints button state
    Serial.print(analogPercent);                //prints analog percentage number
    Serial.println("%");                        //prints req % sign and sets new line
  }
}