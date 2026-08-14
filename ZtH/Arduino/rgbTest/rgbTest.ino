#define redPin 9
#define greenPin 10
#define bluePin 11

void setup() {
  Serial.begin(9600);

  //set led pins to output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  ledRed();
  delay(1000);
  ledGreen();
  delay(1000);
  ledBlue();
  delay(1000);
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