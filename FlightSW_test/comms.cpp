#include "comms.h"

#define TX_D 13
#define RX_D 12

#define DBG 1 //1 for debug statements.

/* comms
  @description: This is a constructor for the communications
  between the bluetooth module and the rest of the program.
  It creates a new instance of SoftwareSerial and sets the
  state of the state machine.
*/
comms::comms() {
  bluetooth = new SoftwareSerial(RX_D, TX_D);
  bluetooth->begin(9600);
  bluetooth->println("Bluetooth test!!!!!!");
  currentState = wait_for_cmd_st;
}

/* transmit
  @description: calls the print() function of the bluetooth
  module for more streamlined bluetooth transmission.

  @param input: The String which will be transmitted to the device
*/
void comms::transmit(String input) {
  bluetooth->print(input);
}

/* transmit
  @description: calls the print() function of the bluetooth
  module for more streamlined bluetooth transmission.

  @param input: the int which will be transmitted to the device
*/
void comms::transmit(int input) {
  bluetooth->print(input);
}

/* tick
  @description: The state machine that handles all incoming
  communication from the bluetooth module. Contains two states,
  'wait_for_cmd_st' and 'relay_cmd_st'. Multiple commands can be waiting
  int the SoftwareSerial object, and will be relayed in the order
  received.

  @return The command from the phone
*/
int8_t comms::tick() {
  int8_t c = 0;
  //Moore outputs
  switch (currentState) {
    case wait_for_cmd_st:
      if (DBG) transmit("wait_for_cmd_st\n");
      break;
    case relay_cmd_st:
      c = bluetooth->read();
      if (DBG) transmit("relay_cmd_st\n");
      break;
  }
  //Mealy Outputs
  switch (currentState) {
    case wait_for_cmd_st:
      if (bluetooth->available())
        currentState = relay_cmd_st;
      break;
    case relay_cmd_st:
      currentState = wait_for_cmd_st;
      break;
  }
  return c;
}
