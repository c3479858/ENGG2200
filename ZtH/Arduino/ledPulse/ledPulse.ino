//Code for flashing onboard LED at a rate of specified Hertz

const int ledPin = 13;
const int hertz = 4;
unsigned long timeLast = 0;
unsigned long timeNow = 0;

int ledState = 0;                               //unused for now

void setup() {
  pinMode(ledPin, OUTPUT);                      //led pin set to output
  Serial.begin(9600);                           //start serial
}

void loop() {
  timeNow = millis();                           //sets timeNow to current millis
  if ((timeNow - timeLast) >= 1000 / hertz) {   //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                         //resets loop
    digitalWrite(ledPin, !digitalRead(ledPin))  //sets led to whatever state it isn't in (in theory)
  }
}