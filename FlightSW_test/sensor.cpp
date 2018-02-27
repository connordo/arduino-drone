#include "sensor.h"
#include "Arduino.h"
#define DBG 1

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

// Register defines courtesy A. Weiss and Nathan Seidle, SparkFun Electronics
#define STATUS     0x00
#define OUT_P_MSB  0x01
#define OUT_P_CSB  0x02
#define OUT_P_LSB  0x03
#define OUT_T_MSB  0x04
#define OUT_T_LSB  0x05
#define DR_STATUS  0x06
#define OUT_P_DELTA_MSB  0x07
#define OUT_P_DELTA_CSB  0x08
#define OUT_P_DELTA_LSB  0x09
#define OUT_T_DELTA_MSB  0x0A
#define OUT_T_DELTA_LSB  0x0B
#define WHO_AM_I   0x0C
#define F_STATUS   0x0D
#define F_DATA     0x0E
#define F_SETUP    0x0F
#define TIME_DLY   0x10
#define SYSMOD     0x11
#define INT_SOURCE 0x12
#define PT_DATA_CFG 0x13
#define BAR_IN_MSB 0x14 // Set at factory to equivalent sea level pressure for measurement location, generally no need to change
#define BAR_IN_LSB 0x15 // Set at factory to equivalent sea level pressure for measurement location, generally no need to change
#define P_TGT_MSB  0x16
#define P_TGT_LSB  0x17
#define T_TGT      0x18
#define P_WND_MSB  0x19
#define P_WND_LSB  0x1A
#define T_WND      0x1B
#define P_MIN_MSB  0x1C
#define P_MIN_CSB  0x1D
#define P_MIN_LSB  0x1E
#define T_MIN_MSB  0x1F
#define T_MIN_LSB  0x20
#define P_MAX_MSB  0x21
#define P_MAX_CSB  0x22
#define P_MAX_LSB  0x23
#define T_MAX_MSB  0x24
#define T_MAX_LSB  0x25
#define CTRL_REG1  0x26
#define CTRL_REG2  0x27
#define CTRL_REG3  0x28
#define CTRL_REG4  0x29
#define CTRL_REG5  0x2A
#define OFF_P      0x2B
#define OFF_T      0x2C
#define OFF_H      0x2D


static void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
static void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

sensor::sensor() {
  accel_x = 0;
  accel_y = 0;
  accel_z = 0;
  gyro_x = 0;
  gyro_y = 0;
  gyro_z = 0;
  altitude = 0;
  accel_x_bias = 0;
  accel_y_bias = 0;
  accel_z_bias = 0;
  gyro_x_bias = 0;
  gyro_y_bias = 0;
  gyro_z_bias = 0;

  Wire.begin(); //allows for I2C Transaction

  I2CwriteByte(MPU9250_ADDRESS, 0x1b, GYRO_FULL_SCALE_2000_DPS); //configure the gyroscope
  I2CwriteByte(MPU9250_ADDRESS, 0x1c, ACC_FULL_SCALE_16_G); //configure the accelerometer
  //  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02); //set the bypass bit
  I2CwriteByte(MPL3115A2_ADDRESS, CTRL_REG1, 0x04); // Set RST (bit 2) to 1

  I2CwriteByte(MPL3115A2_ADDRESS, CTRL_REG1, 0xB9);
  I2CwriteByte(MPL3115A2_ADDRESS, PT_DATA_CFG, 0x07);

  if (DBG) Serial.begin(9600);
}

void sensor::calibrate() {
  int accel_x_bias_temp = 0;
  int accel_y_bias_temp = 0;
  for (int i = 0; i < 5; i++) {
    updateTelemetry();
    accel_x_bias_temp += accel_x;
    accel_y_bias_temp += accel_y;
    delay(500);
  }
  accel_x_bias += accel_x_bias_temp / 5;
  accel_y_bias += accel_y_bias_temp / 5;
  if (DBG)Serial.println("*********************************end calibration");
}

/* imuTest
  @description: initializes the imu. Checks the WHO_AM_I register
  to verify a secure i2c connection.

  @return: 0 if successful. nonzero otherwise.
*/
bool sensor::imuTest() {
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
bool sensor::altTest() {//TODO fix this function. It's not working proplerly, but the altimeter IS showing up on the bus.
  uint8_t return_value = 0;
  I2Cread(MPL3115A2_ADDRESS, ALT_WHO_AM_I, 1, &return_value);
  if (return_value == ALT_WAI_RET_VAL) {
    return 0;
  }
  else {
    if (DBG) Serial.print("**Return value was: ");
    if (DBG) Serial.print(return_value);
    if (DBG) Serial.println("**");
    return -1;
  }
}

/* updateTelemetry
  @description: updates the acceleromter, gyroscope, and altitude data.

  @return: 0 if successful. nonzero otherwise.
*/
int sensor::updateTelemetry() {
  uint8_t IMU_Buf[14] = {0};
  uint8_t ALT_Buf[6] = {0};
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, IMU_Buf);
  I2CwriteByte(MPL3115A2_ADDRESS, CTRL_REG1, 0xB9);
  I2Cread(MPL3115A2_ADDRESS, 0x00, 6, ALT_Buf);

  // Create 16 bits values from 8 bits data
  // Accelerometer
  accel_x = -(IMU_Buf[0] << 8 | IMU_Buf[1]); //TODO check the negative values. What's that about? lolz
  accel_y = -(IMU_Buf[2] << 8 | IMU_Buf[3]);
  accel_z = IMU_Buf[4] << 8 | IMU_Buf[5];

  // Gyroscope
  gyro_x = -(IMU_Buf[8] << 8 | IMU_Buf[9]);
  gyro_y = -(IMU_Buf[10] << 8 | IMU_Buf[11]);
  gyro_z = IMU_Buf[12] << 8 | IMU_Buf[13];

  //Connor's test code
  Serial.println("<Connor's Test Code>");
  Serial.println(ALT_Buf[0]);
  Serial.println(ALT_Buf[1]);
  Serial.println(ALT_Buf[2]);
  Serial.println(ALT_Buf[3]);
  Serial.println(ALT_Buf[4]);
  Serial.println("</Connor's Test Code>");
  //
  int tHeight = (((int32_t)(ALT_Buf[1] * (int32_t)65536) + (ALT_Buf[2] * 256) + (ALT_Buf[3] & 0xF0)) / 16);
  altitude = tHeight / 16.0;

}

/* toString
  @description: packages the telemetry into a string that can be printed

  @return: the String of telemetry data.
*/
String sensor::toString() {
  String output;
  output = String(accel_x) + "\t" + String(accel_y) + "\t" + String(accel_z) + "\t" + String(gyro_x) + "\t" + String(gyro_y) + "\t" + String(gyro_z) + "\t" + String(altitude);
  return output;
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
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
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}
