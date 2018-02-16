#include "comms.h"

#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

comms::comms() {
  bluetooth = new SoftwareSerial(RX_D, TX_D);
  bluetooth->begin(9600);
  bluetooth->println("Bluetooth test!!!!!!");
  currentState = wait_for_cmd;
}

void comms::transmit(String input) {
  bluetooth->print(input);
}

void comms::transmit(int input) {
  bluetooth->print(input);
}

int8_t comms::tick() {
  int8_t c = 0;
  //Moore outputs
  switch (currentState) {
    case wait_for_cmd:
      transmit("wait_for_cmd\n");
      break;
    case relay_cmd:
      c = bluetooth->read();
      transmit("relay_cmd\n");
      break;
  }
  //Mealy Outputs
  switch (currentState) {
    case wait_for_cmd:
      if (bluetooth->available())
        currentState = relay_cmd;
      break;
    case relay_cmd:
      currentState = wait_for_cmd;
      break;
  }
  return c;
}
