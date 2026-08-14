const int redLed = pwm1;    //replace pwm1 with chosen pwm pin
const int greenLed = pwm2;  //replace pwm2 with chosen pwm pin
const int blueLed = pwm3;   //replace pwm3 with chosen pwm pin



void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  rgbFade(14, 117, 184);
  delay(500);
  digitalWrite(redLed, 0);
  digitalWrite(greenLed, 0);
  digitalWrite(blueLed, 0);
}

void rgbFade(r, g, b) {  //fades specified rgb colour in from 0% to 100% brightness
  for (int i = 0; i < 100; i++) {
    digitalWrite(redLed, (i / 100.0) * r);
    digitalWrite(greenLed, (i / 100.0) * g);
    digitalWrite(blueLed, (i / 100.0) * b);
    delay(20);
  }
}