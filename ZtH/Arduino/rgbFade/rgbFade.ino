#define redLed 9
#define greenLed 10
#define blueLed 11



void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  rgbFade(14, 117, 184);
  delay(500);
  analogWrite(redLed, 0);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);
  delay(500);
}

void rgbFade(int r, int g, int b) {  //fades specified rgb colour in from 0% to 100% brightness
  for (int i = 0; i < 100; i++) {
    analogWrite(redLed, (i / 100.0) * r);
    analogWrite(greenLed, (i / 100.0) * g);
    analogWrite(blueLed, (i / 100.0) * b);
    delay(20);
  }
}