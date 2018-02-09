#include "sensor.h"


//Slave Addresses
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C
#define    MPL3115A2_ADDRESS          0x60

// Address locations for the IMU
#define    MPU_WHO_AM_I               0x75 //should return 0x71
#define    MPU_WAI_RET_VAL            0x71

#define    GYRO_FULL_SCALE_250_DPS    0x00 //degrees per second
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G         0x00 //something to do with sample rate
#define    ACC_FULL_SCALE_4_G         0x08
#define    ACC_FULL_SCALE_8_G         0x10
#define    ACC_FULL_SCALE_16_G        0x18

// Address locations for the ALT
#define    ALT_WHO_AM_I               0x0C //returns 0xc4 if successful
#define    ALT_WAI_RET_VAL            0xC4


sensor::sensor() {
  accel_x = 0;
  accel_y = 0;
  accel_z = 0;
  gyro_x = 0;
  gyro_y = 0;
  gyro_z = 0;
  altitude = 0;

}

/* imuTest
  @description: initializes the imu. Checks the WHO_AM_I register
  to verify a secure i2c connection.

  @return: 0 if successful. nonzero otherwise.
*/
int sensor::imuTest() {
  uint8_t return_value = 0;
  I2Cread(MPU9250_ADDRESS, MPU_WHO_AM_I, 1, &return_value);
  if (return_value == MPU_WAI_RET_VAL) {
    return 0;
  }
  else {
    return -1;
  }
}

/* altTest
  @description: initializes the imu. Checks the WHO_AM_I register
  to verify a secure i2c connection.

  @return: 0 if successful. nonzero otherwise.
*/
int sensor::altTest() {
  uint8_t return_value = 0;
  I2Cread(MPL3115A2_ADDRESS, ALT_WHO_AM_I, 1, &return_value);
  if (return_value == ALT_WAI_RET_VAL) {
    return 0;
  }
  else {
    return -1;
  }
}

/* updateTelemetry
  @description: updates the acceleromter, gyroscope, and altitude data.

  @return: 0 if successful. nonzero otherwise.
*/
int sensor::updateTelemetry() {
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  // Create 16 bits values from 8 bits data

  // Accelerometer
  accel_x = -(Buf[0] << 8 | Buf[1]);//TODO check the negative values. What's that about? lolz
  accel_y = -(Buf[2] << 8 | Buf[3]);
  accel_z = Buf[4] << 8 | Buf[5];

  // Gyroscope
  gyro_x = -(Buf[8] << 8 | Buf[9]);
  gyro_y = -(Buf[10] << 8 | Buf[11]);
  gyro_z = Buf[12] << 8 | Buf[13];
}

void sensor::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}

// Write a byte (Data) in device (Address) at register (Register)
void sensor::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}
