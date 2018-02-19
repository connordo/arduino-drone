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
  bbcomms = new comms();
  bbatt = new attitude();
  if (DBG) Serial.println("sensor object created");
  if (DBG) {
    Serial.print("IMU CHECK: ");
    bbsensors->imuTest() ? Serial.println("Failed") : Serial.println("Passed");
    Serial.print("ALTIMETER value: ");
    bbsensors->altTest() ? Serial.println("Failed") : Serial.println("Passed");
    //Serial.println(bbsensors->altTest());
  }
  // if(DBG) bluetooth.println("Bluetooth test");
}

void loop() {
  if (DBG)
    Serial.print(bbsensors->toString());
  delay(1000);

  //  bbsensors->updateTelemetry();
  int8_t cmd = bbcomms->tick();
  bbatt->tick((char)cmd);

}
