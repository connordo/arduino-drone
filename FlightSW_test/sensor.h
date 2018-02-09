#ifndef sensor_h
#define sensor_h

#include <Wire.h>

class sensor {
  public:
  
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t altitude;

  public:
    sensor();
    bool imuTest();
    bool altTest();
    int updateTelemetry();
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

};

#endif
