#include <softserial.h>

#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

int comms_init(){
  SoftwareSerial bluetooth(RX_D, TX_D);
}
