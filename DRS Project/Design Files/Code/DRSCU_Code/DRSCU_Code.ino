#include <FlexCAN_T4.h>
#include <PWMServo.h>

#define ledPin 13
#define servoPin 19

//Servo Setup 1
PWMServo drs;
int openAngle = 95;    //angle to open servo to (in degrees) Change if required
int closedAngle = 80;  //angle to close servo to (in degrees) Change when required

//Timer Setup
unsigned long timeNow = 0;
unsigned long timeLast = 0;
unsigned long stateChange = 0;
const unsigned long debounceDelay = 200;

// CAN Setup
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t incoming_msg;
CAN_message_t outgoing_msg;
int msg_read = 0;

const int baudRate = 1000;  //CAN baud rate in kb/s

void setup() {
  //Servo set up 2 (to avoid 0-90-0 sweep)
  analogWriteFrequency(servoPin, 67);  // 67Hz servo frequency (teehee)
  analogWrite(servoPin, 0);            // NO MOVE THE SERVO
  delay(100);
  drs.attach(servoPin);
  drs.write(closedAngle);

  can1.begin();
  can1.setBaudRate(int(baudRate * 1000.0));

  Serial.begin(9600);  //start serial
  pinMode(ledPin, OUTPUT);

  /*debug
  Serial.println(int(baudRate * 1000.0));
  drs.write(openAngle);
  digitalWrite(ledPin, HIGH);
  delay(1500);
  drs.write(closedAngle);
  digitalWrite(ledPin, LOW);*/
}

void loop() {
  timeNow = millis();
  msg_read = can1.read(incoming_msg);  //sets msg_read to true (1) if message has been read

  if (msg_read == 1 && incoming_msg.id == 20 && (timeNow - stateChange >= debounceDelay)) {
    if (incoming_msg.buf[0] == 1) {
      drs.write(openAngle);  //open the wing to set angle
      digitalWrite(ledPin, HIGH);
      Serial.println("Wing open");

    } else if (incoming_msg.buf[0] == 0) {
      drs.write(closedAngle);  //close wing to set angle
      digitalWrite(ledPin, LOW);
      Serial.println("Wing closed");
    }
    timeLast = timeNow;

  } else if (timeNow - timeLast >= 5000) {
    drs.write(closedAngle);
    Serial.println("No signal detected. Wing closed");
    digitalWrite(ledPin, LOW);
    timeLast = timeNow;
  }
}