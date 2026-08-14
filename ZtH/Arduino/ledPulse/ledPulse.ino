//Code for flashing onboard LED at a rate of specified Hertz

const int ledPin = 13;
const int hertz = 4;
unsigned long timeLast = 0;
unsigned long timeNow = 0;

int ledState = 0;  //unused for now

void setup() {
  pinMode(ledPin, OUTPUT);  //led pin set to output
  Serial.begin(9600);       //start serial at 9600baud
}

void loop() {
  pulse(ledPin, 5);
}

void pulse(int pin, int hertz) {
  timeNow = millis();                          //sets timeNow to current millis
  if ((timeNow - timeLast) >= 500 / hertz) {  //if loop, checks to see if 1/htz seconds have passed
    timeLast = timeNow;                        //resets loop
    digitalWrite(pin, !digitalRead(pin));      //sets led to whatever state it isn't in (in theory)
  }
}