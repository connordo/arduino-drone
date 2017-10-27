#include <Wire.h>
//Arduino PWM pins
#define MOTOR_1 10 //Arduino PWM pin
#define MOTOR_2 9 //Arduino PWM pin
#define MOTOR_3 6 //Arduino PWM pin
#define MOTOR_4 11 //Arduino PWM pin

//Motor Speeds
#define HIGH_SPEED 255
#define HOVER_SPEED 0
#define LOW_SPEED 1

//Slave Addresses
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

//Configuration Settings
#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

//Average Values
#define ACC_REST_VAL_X -365 //calculated in MatLab
#define ACC_REST_VAL_Y -178 //calculated in MatLab
#define ACC_REST_VAL_Z 1580 //calculated in MatLab
#define BUFFER 400
//Gyroscope Tolerance Thresholds
#define GX_MAX 100
#define GX_MIN -100
#define GY_MAX 100
#define GY_MIN -100
#define GZ_MAX 100
#define GZ_MIN -100

//HIGH_SPEEDerometer Tolerance Thresholds
#define AX_MAX (ACC_REST_VAL_X+BUFFER)//-65
#define AX_MIN (ACC_REST_VAL_X-BUFFER)//-665
#define AY_MAX (ACC_REST_VAL_Y+BUFFER)//222
#define AY_MIN (ACC_REST_VAL_Y-BUFFER)//-478
#define AZ_MAX (ACC_REST_VAL_Z+BUFFER)//2080
#define AZ_MIN (ACC_REST_VAL_Z-BUFFER)//1080

//Shortcuts
#define HIGH_SPEED_X_WITHIN_THRESH (*ax<AX_MAX&&*ax>AX_MIN)
#define HIGH_SPEED_Y_WITHIN_THRESH (*ay<AY_MAX&&*ay>AY_MIN)
#define HIGH_SPEED_Z_WITHIN_THRESH (*az<AZ_MAX&&*az>AZ_MIN)
#define GYRO_X_WITHIN_THRESH (gx<GX_MAX&&gx>GX_MIN)
#define GYRO_Y_WITHIN_THRESH (gy<GY_MAX&&gy>GY_MIN)
#define GYRO_X_WITHIN_THRESH (gz<GZ_MAX&&gz>GZ_MIN)

//States
#define ST_INIT 0
#define ST_STBL 1
#define ST_USTBL 2

//Board Angles
#define OVER_POSITIVE 1
#define IN_SPEC 0;
#define OVER_NEGATIVE -1

//Global Variables
int16_t ax;
int16_t ay;
int16_t az;
int16_t gx;
int16_t gy;
int16_t gz;

/*---I2Cread---
   @description:
   reads a specific register from a designated slave address. Can fill a
   buffer of Nbytes size.

   @parameters:
   uint8_t Address: the slave address (hex)
   uint8_t Register: The register to be read on the slave
   uint8_t Nbytes: the number of bytes in the buffer.
   uint8_t* Data: pointer to an array of buffers

   @return:
   void
*/
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
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


/*---I2CwriteByte---
   @description:
   Writes a byte of data over i2c to the designated register on the chosen slave.

   @parameters:
   uint8_t Address: the slave address being written to
   uint8_t Register: the register on the slave being written to
   uint8_t Data: the byte to be written

   @return:
   void
*/
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

/*---update_IMU_data---
   @description:
   This function updates the six datapoints of the IMU. It reads the 12 registers on the IMU
   corresponding to the accelerometer and gyroscope. Then, it compiles the 12 numbers into the
   six values and returns them.

   @parameters:
   int16_t* ax: X-axis of the accelerometer. Passed by reference
   int16_t* ay: Y-axis of the accelerometer. Passed by reference
   int16_t* az: Z-axis of the accelerometer. Passed by reference
   int16_t* gx: x-axis of the gyroscope. Passed by reference
   int16_t* gy: Y-axis of the gyroscope. Passed by reference
   int16_t* gz: z-axis of the gyroscope. Passed by reference

   @return:
   void
*/
void update_IMU_data(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  // HIGH_SPEEDerometer
  *ax = -(Buf[0] << 8 | Buf[1]);
  *ay = -(Buf[2] << 8 | Buf[3]);
  *az = Buf[4] << 8 | Buf[5];

  // Gyroscope
  *gx = -(Buf[8] << 8 | Buf[9]);
  *gy = -(Buf[10] << 8 | Buf[11]);
  *gz = Buf[12] << 8 | Buf[13];

  // HIGH_SPEEDerometer
  Serial.print (*ax, DEC);
  Serial.print ("\t");
  Serial.print (*ay, DEC);
  Serial.print ("\t");
  Serial.print (*az, DEC);
  Serial.print ("\t");
  // Gyroscope
  Serial.print (*gx, DEC);
  Serial.print ("\t");
  Serial.print (*gy, DEC);
  Serial.print ("\t");
  Serial.print (*gz, DEC);
  Serial.print ("\t");
  Serial.println("");
}
/*---x_conversion---
   @description:
   converts the X-axis reading from the IMU into a PWM value

   @parameter:
   uint16_t the raw value from the IMU

   @return:
   the PWM value.
*/
uint16_t x_conversion(uint16_t xaxis) {
  return ((xaxis + 2314) / 15.35);
}

/*---y_conversion---
   @description:
   converts the Y-axis reading from the IMU into a PWM value

   @parameter:
   uint16_t the raw value from the IMU

   @return:
   the PWM value
*/
uint16_t y_conversion(uint16_t yaxis) {
  return ((yaxis + 2140.55) / 15.45);
}


void setup() {
  int state = 0;
  Serial.begin(9600);
  Wire.begin();

  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  // Configure HIGH_SPEEDerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  // Request first magnetometer single measurement
  //  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01); //I rdon't think I wasnt to do this yet....

  Serial.write("Beginning I2C Read Attempt:\n");


  ///////////////
  analogWrite(MOTOR_1, HIGH_SPEED);
  delay(500);
  analogWrite(MOTOR_1, HOVER_SPEED);
  delay(500);

  analogWrite(MOTOR_2, HIGH_SPEED);
  delay(500);
  analogWrite(MOTOR_2, HOVER_SPEED);
  delay(500);

  analogWrite(MOTOR_3, HIGH_SPEED);
  delay(500);
  analogWrite(MOTOR_3, HOVER_SPEED);
  delay(500);

  analogWrite(MOTOR_4, HIGH_SPEED);
  delay(500);
  analogWrite(MOTOR_4, HOVER_SPEED);
  delay(500);
  ///////////////
}

long int cpt = 0; //this is a counter

void loop() {
  update_IMU_data(&ax, &ay, &az, &gx, &gy, &gz);
  analogWrite(MOTOR_1, x_conversion(ax));
  analogWrite(MOTOR_2, x_conversion(ax));
  analogWrite(MOTOR_3, 255 - x_conversion(ax));
  analogWrite(MOTOR_4, 255 - x_conversion(ax));

}

