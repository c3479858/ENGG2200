#include <FlexCAN_T4.h>

//Servo Setup
#define servoPin 19   //servo signal PWM pin
int openAngle = 30;   //angle to open servo to (in degrees, might change this to be raw bit value or radians or percentage of limit, idk)
int closedAngle = 0;  //angle to close servo to (in degrees)

//Timeout Setup
unsigned long timeNow = 0;
unsigned long timeLast = 0;

// CAN Setup
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t incoming_msg;
CAN_message_t outgoing_msg;
int msg_read = 0;
int baudRate = 1000;  //CAN baud rate in kb/s

void setup() {
  pinMode(servoPin, OUTPUT);

  can1.begin();
  can1.setBaudRate(baudRate * 1000);
  Serial.begin(9600);  //start serial

  //outgoing_msg.id = 0;              // Message ID. Decimal, 0-2047
  //outgoing_msg.flags.remote = 0;    // RTR - 0 for standard data frames
  //outgoing_msg.flags.extended = 0;  // IDE - 0 for standard 11-bit IDs
  //outgoing_msg.flags.reserved = 0;  // Reserved bit. Leave as dominant (0)
  //outgoing_msg.len = 1;             // DLC. How many bytes to send.
  //outgoing_msg.flags.overrun = 0;   // Leave as dominant (0)
}

void loop() {
  timeNow = millis();

  msg_read = can1.read(incoming_msg);  //sets msg_read to true (1) if message has been read
  if ((msg_read) && incoming_msg.id == 20) {
    if (incoming_msg.buf[0] == 1) {
      analogWrite(servoPin, (openAngle / 360) * 255);  //placeholder to open the wing (need to find values for this)
      Serial.println("Wing open");
    } else if (incoming_msg.buf[0] == 0) {
      analogWrite(servoPin, (closedAngle / 360) * 255);  //placeholder for closing the wing, same thing ^
      Serial.println("Wing closed");
    }
    timeLast = timeNow;
    //outgoing_msg.buf[0] = S;
    //can1.write(outgoing_msg);
  } else if (timeNow - timeLast >= 5000) {
    analogWrite(servoPin, "close");
    Serial.println("No signal detected. Wing closed");
  }
  timeLast = timeNow;
}