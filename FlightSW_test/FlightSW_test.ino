#include "sensor.h"
#include "comms.h"
#include "attitude.h"

#define DBG 1

sensor *bbsensors;
comms *bbcomms;
attitude *bbatt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // bluetooth.begin(9600);
  if (DBG) Serial.println("DBG is set to one. Debug Statements will print");

  bbsensors = new sensor();
  if (DBG) Serial.println("sensor object created");
  if (DBG) {
    Serial.print("IMU CHECK: ");
    bbsensors->imuTest() ? Serial.println("Failed") : Serial.println("Passed");
    Serial.print("ALTIMETER value: ");
    bbsensors->altTest() ? Serial.println("Failed") : Serial.println("Passed");
  }
  delete bbsensors;
  bbcomms = new comms();
  bbatt = new attitude();
}

void loop() {
  //  if (DBG) Serial.println(bbsensors->toString());
  //  delay(1000);

  int8_t cmd = bbcomms->tick();
  if (cmd) Serial.println((char)cmd);
  bbatt->tick(cmd);

}
