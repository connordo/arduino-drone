//#include <QueueArray.h>
#include "sensor.h"
#include "comms.h"

#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

#define DBG 1

// SoftwareSerial bluetooth(RX_D, TX_D);
sensor *bbsensors;
comms *bbcomms;
//QueueArray<char> commands;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // bluetooth.begin(9600);
  if (DBG) Serial.println("DBG is set to one. Debug Statements will print");
  bbsensors = new sensor();
  bbcomms = new comms();
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
  if (DBG) {
    Serial.print(bbsensors->accel_x);
    Serial.print("\t");
    Serial.print(bbsensors->accel_y);
    Serial.print("\t");
    Serial.print(bbsensors->accel_z);
    Serial.print("\t");
    Serial.print(bbsensors->gyro_x);
    Serial.print("\t");
    Serial.print(bbsensors->gyro_y);
    Serial.print("\t");
    Serial.print(bbsensors->gyro_z);
    Serial.print("\n");
  }
  delay(1000);
  bbsensors->updateTelemetry();
  int8_t cmd = bbcomms->tick();
  //  if (cmd) commands.push(char(cmd));

}
