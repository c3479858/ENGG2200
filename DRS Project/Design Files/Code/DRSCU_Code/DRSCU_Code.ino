#include <FlexCAN_T4.h>
#include <Servo.h>
//Servo Setup
Servo drs;

int openAngle = 0;     //angle to open servo to (in degrees, might change this to be raw bit value or radians or percentage of limit, idk)
int closedAngle = 30;  //angle to close servo to (in degrees)

//Timeout Setup
unsigned long timeNow = 0;
unsigned long timeLast = 0;

// CAN Setup
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t incoming_msg;
CAN_message_t outgoing_msg;
int msg_read = 0;

const int baudRate = 1000;  //CAN baud rate in kb/s
const int ledPin = 13;

void setup() {
  drs.attach(19);

  can1.begin();
  can1.setBaudRate(int(baudRate * 1000.0));
  Serial.begin(9600);  //start serial
  pinMode(ledPin, OUTPUT);
  
  //debug
  Serial.println(int(baudRate * 1000.0));
  drs.write(openAngle);
  digitalWrite(ledPin, HIGH);
  delay(1500);
  drs.write(closedAngle);
  digitalWrite(ledPin, LOW);
}

void loop() {
  timeNow = millis();
  msg_read = can1.read(incoming_msg);  //sets msg_read to true (1) if message has been read

  if (msg_read == 1) {
    digitalWrite(ledPin, HIGH);

    if (incoming_msg.buf[0] == 1) {
      drs.write(openAngle);  //placeholder to open the wing (need to find values for this)
      Serial.println("Wing open");

    } else if (incoming_msg.buf[0] == 0) {
      drs.write(closedAngle);  //placeholder for closing the wing, same thing ^
      Serial.println("Wing closed");
    }
    timeLast = timeNow;
    //outgoing_msg.buf[0] = S;
    //can1.write(outgoing_msg);
  } else if (timeNow - timeLast >= 5000) {
    digitalWrite(ledPin, LOW);
    drs.write(closedAngle);
    Serial.println("No signal detected. Wing closed");
    timeLast = timeNow;
    Serial.println(msg_read);
  }
}