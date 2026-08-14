#define redLed 9
#define greenLed 10
#define blueLed 11



void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(9600);

  rgbDisplay(14, 117, 184);
}

void loop() {
}

void rgbDisplay(int r, int g, int b) {  //sets specified rgb colour
  analogWrite(redLed, r);
  analogWrite(greenLed, g);
  analogWrite(blueLed, b);
}