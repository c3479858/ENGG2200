const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

void setup() {
  Serial.begin(9600);

  //set led pins to output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  ledRed();
  delay(250);
  ledGreen();
  delay(250);
  ledBlue();
  delay(250);
}

void ledRed() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ledGreen() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void ledBlue() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}