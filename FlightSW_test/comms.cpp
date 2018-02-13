#include "comms.h"

#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

comms::comms() {
  SoftwareSerial bluetooth(RX_D, TX_D);
  bluetooth.begin(9600);
  bluetooth.println("Bluetooth test");

}

void comms::tick(){

}
