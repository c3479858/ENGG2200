#include <FlexCAN_T4.h>

// Create variables. Outside the setup/loop functions so that they are global.
// Create a FlexCAN_T4 object for the CAN network
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t incoming_msg;
CAN_message_t outgoing_msg;
int msg_read = 0;

//initialising values
int x = 0;
int y = 0;
int z = 0;
int S = 0;

void setup() {
  can1.begin();
  can1.setBaudRate(500000); //kb/s
  Serial.begin(9600);       //start serial

  outgoing_msg.id = 0;            // Message ID. Decimal, 0-2047
  outgoing_msg.flags.remote = 0;    // RTR - 0 for standard data frames
  outgoing_msg.flags.extended = 0;  // IDE - 0 for standard 11-bit IDs
  outgoing_msg.flags.reserved = 0;  // Reserved bit. Leave as dominant (0)
  outgoing_msg.len = 1;             // DLC. How many bytes to send.
  outgoing_msg.flags.overrun = 0;   // Leave as dominant (0)
}

void loop() {
  msg_read = can1.read(incoming_msg);       //sets msg_read to true (1) if message has been read
  if (msg_read){
    //computes solution for S according to capstone details
    x = (0.1 * incoming_msg.buf[0]) + 3;
    y = (0.2 * incoming_msg.buf[1]) + 2;
    z = (0.3 * incoming_msg.buf[2]) + 5;
    S = (2 * x) + (y * z);

    //sets outgoing message to S, with scaling factor 1 and no offset
    outgoing_msg.buf[0] = S;
    can1.write(outgoing_msg);
    Serial.println("Message sent!")
    //mostly for debugging, but helpful to see on serial
  }else{
    Serial.println("Waiting for message...")
    delay(1000)
  }
}