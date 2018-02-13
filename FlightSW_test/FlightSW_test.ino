#include <SoftwareSerial.h>
#include "sensor.h"

#define TX_D 8 //These are subject to change
#define RX_D 7 //These are subject to change

#define DBG 1

SoftwareSerial bluetooth(RX_D, TX_D);
sensor *bbsensors;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (DBG) Serial.println("DBG is set to one. Debug Statements will print");
  bbsensors = new sensor();
  if (DBG) Serial.println("sensor object created");

  bbsensors->imuTest()?Serial.println("Failed"):Serial.println("passed");
}

void loop() {
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
 
  delay(1000);
  Serial.println(bbsensors->updateTelemetry());

}
