#include <Wire.h>
//Arduino PWM pins
#define MOTOR_1 10 //Arduino PWM pin
#define MOTOR_2 9 //Arduino PWM pin
#define MOTOR_3 6 //Arduino PWM pin
#define MOTOR_4 11 //Arduino PWM pin

//Motor Speeds
#define ACCEL 255
#define STABL 0
#define DECEL 10

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

//Accelerometer Tolerance Thresholds
#define AX_MAX (ACC_REST_VAL_X+BUFFER)//-65
#define AX_MIN (ACC_REST_VAL_X-BUFFER)//-665
#define AY_MAX (ACC_REST_VAL_Y+BUFFER)//122
#define AY_MIN (ACC_REST_VAL_Y-BUFFER)//-478
#define AZ_MAX (ACC_REST_VAL_Z+BUFFER)//2080
#define AZ_MIN (ACC_REST_VAL_Z-BUFFER)//1080

//Shortcuts
#define ACCEL_X_WITHIN_THRESH (*ax<AX_MAX&&*ax>AX_MIN)
#define ACCEL_Y_WITHIN_THRESH (*ay<AY_MAX&&*ay>AY_MIN)
#define ACCEL_Z_WITHIN_THRESH (*az<AZ_MAX&&*az>AZ_MIN)
#define GYRO_X_WITHIN_THRESH (gx<GX_MAX&&gx>GX_MIN)
#define GYRO_Y_WITHIN_THRESH (gy<GY_MAX&&gy>GY_MIN)
#define GYRO_X_WITHIN_THRESH (gz<GZ_MAX&&gz>GZ_MIN)

//States
#define ST_INIT 0
#define ST_STBL 1
#define ST_USTBL 2

//Global Variables
int16_t ax;
int16_t ay;
int16_t az;
int16_t gx;
int16_t gy;
int16_t gz;

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

// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void update_IMU_data(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
  // Accelerometer
  *ax = -(Buf[0] << 8 | Buf[1]);
  *ay = -(Buf[2] << 8 | Buf[3]);
  *az = Buf[4] << 8 | Buf[5];

  // Gyroscope
  *gx = -(Buf[8] << 8 | Buf[9]);
  *gy = -(Buf[10] << 8 | Buf[11]);
  *gz = Buf[12] << 8 | Buf[13];

  // Accelerometer
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

bool is_stable(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
  if (((*ax < AX_MAX) && (*ax > AX_MIN)) && ((*ay < AY_MAX) && (*ay > AY_MIN)) && ((*az < AZ_MAX) && (*az > AZ_MIN)))
  {
    analogWrite(MOTOR_1, STABL);
    analogWrite(MOTOR_2, STABL);
    analogWrite(MOTOR_3, STABL);
    analogWrite(MOTOR_4, STABL);
    return true;
  }
  else return false;
}

void self_correct(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
  analogWrite(MOTOR_1, ACCEL);
  analogWrite(MOTOR_2, ACCEL);
  analogWrite(MOTOR_3, ACCEL);
  analogWrite(MOTOR_4, ACCEL);
}

void setup() {
  int state = 0;
  Serial.begin(9600);
  Wire.begin();

  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  // Request first magnetometer single measurement
  //  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01); //I rdon't think I wasnt to do this yet....

  Serial.write("Beginning I2C Read Attempt:\n");
}

long int cpt = 0; //this is a counter

void loop() {
  int state = 0;
  bool val = 5;

  update_IMU_data(&ax, &ay, &az, &gx, &gy, &gz);
  val = is_stable(&ax, &ay, &az, &gx, &gy, &gz);
  if (!val)
  {
    Serial.println(val);
    self_correct(&ax, &ay, &az, &gx, &gy, &gz);
  }

  //  // MOORE Outputs
  //  switch (state) {
  //    case ST_INIT:
  //      break;
  //    case ST_STBL:
  //      analogWrite(MOTOR_1, STABL);
  //      analogWrite(MOTOR_2, STABL);
  //      analogWrite(MOTOR_3, STABL);
  //      analogWrite(MOTOR_4, STABL);
  //      break;
  //    case ST_USTBL:
  //      analogWrite(MOTOR_1, ACCEL);
  //      analogWrite(MOTOR_2, ACCEL);
  //      analogWrite(MOTOR_3, ACCEL);
  //      analogWrite(MOTOR_4, ACCEL);
  //      break;
  //  }
  //
  //  //MEALY outputs
  //  switch (state) {
  //    case ST_INIT:
  //      if (!(ACCEL_X_WITHIN_THRESH)) state = ST_USTBL;
  //      else if (ACCEL_X_WITHIN_THRESH) state = ST_STBL;
  //      break;
  //    //--------------------------------------
  //    case ST_STBL:
  //      if (!(ACCEL_X_WITHIN_THRESH) || !(ACCEL_Y_WITHIN_THRESH) || !(ACCEL_Z_WITHIN_THRESH)) state = ST_USTBL;
  //      break;
  //    //--------------------------------------
  //    case ST_USTBL:
  //      if ((ACCEL_X_WITHIN_THRESH) && (ACCEL_Y_WITHIN_THRESH) && (ACCEL_Z_WITHIN_THRESH)) state = ST_STBL;
  //      break;
  //  }
}

