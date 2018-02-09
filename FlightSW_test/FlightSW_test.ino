#include <SoftwareSerial.h>
#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

#define DBG 1

SoftwareSerial bluetooth(RX_D, TX_D);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (DBG) Serial.println("DBG is set to one. Debug Statements will print");

  int checkval = 5;
  if (sensors_init() == 0) {
    if (DBG) Serial.println("All sensors online");
  }
  else {
    if (DBG) Serial.println("Error with sensors");
  }

  SoftwareSerial bluetooth(RX_D, TX_D);
  bluetooth.begin(9600);
}

void loop() {
  byte c;
  bluetooth.begin(9600);
  while (!bluetooth.available());
  Serial.println(bluetooth.available());
  Serial.println(bluetooth.available());
  Serial.println("hi 1");
  c = bluetooth.read();
  Serial.println("hi 2");
  Serial.println(bluetooth.available());
  delay(5000);

}
