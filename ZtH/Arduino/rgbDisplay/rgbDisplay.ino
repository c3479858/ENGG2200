const int redLed = pwm1;    //replace pwm1 with chosen pwm pin
const int greenLed = pwm2;  //replace pwm2 with chosen pwm pin
const int blueLed = pwm3;   //replace pwm3 with chosen pwm pin



void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(9600);

  rgbDisplay(14, 117, 184);
}

void loop() {
}

void rgbDisplay(r, g, b) {  //sets specified rgb colour
  digitalWrite(redLed, r);
  digitalWrite(greenLed, g);
  digitalWrite(blueLed, b);
}