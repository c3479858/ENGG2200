// Include the FlexCAN Library
#include <FlexCAN_T4.h>
// Include the FastLED Library (for EVERY_N_MILLISECONDS)
#include <FastLED.h>

// Create variables. Outside the setup/loop functions so that they are global.
// Create a FlexCAN_T4 object for the CAN network
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
// Create a CAN_message_t object for outgoing messages.
CAN_message_t outgoing_msg;

void setup(void) {
  // Initialise the bus and set the Baud rate.
  can1.begin();
  can1.setBaudRate(500000);  // kb/s
  // Initialise the serial monitor
  Serial.begin(9600);

  // Initialise the CAN message parameters
  outgoing_msg.id = 0;              // Message ID. Decimal, 0-2047
  outgoing_msg.flags.remote = 0;    // RTR - 0 for standard data frames
  outgoing_msg.flags.extended = 0;  // IDE - 0 for standard 11-bit IDs
  outgoing_msg.flags.reserved = 0;  // Reserved bit. Leave as dominant (0)
  outgoing_msg.len = 1;             // DLC. How many bytes to send.
  outgoing_msg.flags.overrun = 0;   // Leave as dominant (0)
  //outgoing_msg.buf[0] = 1;          // Data payload, byte 0, 0-255.
}

void loop() {
  // Every 200 ms, do a thing
  EVERY_N_MILLISECONDS(2000) {
    // Write message to CAN BUS
    can1.write(outgoing_msg);
  }
}