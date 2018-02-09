#include <Wire.h>

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


/*sensors_check_imu
  @description: initializes the imu. Checks the WHO_AM_I register
  to verify a secure i2c connection.

  @return: 0 if successful. nonzero otherwise.
*/
int sensors_check_imu() {
  uint8_t return_value = 0;
  I2Cread(MPU9250_ADDRESS, MPU_WHO_AM_I, 1, &return_value);
  if (return_value == MPU_WAI_RET_VAL) {
    if (DBG) Serial.println("IMU is online");
    return 0;
  }
  else {
    if (DBG) Serial.println("IMU is OFFLINE");
    return false;
  }
}

/*sensors_check_alt
  @description: initializes the imu. Checks the WHO_AM_I register
  to verify a secure i2c connection.

  @return: 0 if successful. nonzero otherwise.
*/
int sensors_check_alt() {
  uint8_t return_value = 0;
  I2Cread(MPL3115A2_ADDRESS, ALT_WHO_AM_I, 1, &return_value);
  if (return_value == ALT_WAI_RET_VAL) {
    if (DBG) Serial.println("ALT is online");
    return 0;
  }
  else {
    if (DBG) Serial.println("ALT is OFFLINE");
    if (DBG) Serial.print(return_value);
    if (DBG) Serial.println(" Was returned");

    return false;
  }
}

/*sensors_init
  @description: initializes the i2c communication and checks the IMU and ALT
  to ensure proper i2c connection is in place.

  @return: 0 if successful. nonzero otherwise.
*/
int sensors_init() {
  Wire.begin();
  I2CwriteByte(MPU9250_ADDRESS, 0x1b, GYRO_FULL_SCALE_2000_DPS); //configure the gyroscope
  I2CwriteByte(MPU9250_ADDRESS, 0x1c, ACC_FULL_SCALE_16_G); //configure the accelerometer
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02); //set the bypass bit
  int imu_ret = sensors_check_imu();
  int alt_ret = sensors_check_alt();
  if (!imu_ret && !alt_ret)
    return -1;
  else return 0;
}
