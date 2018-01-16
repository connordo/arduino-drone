// Code written by Connor Olsen

#define IMU_ADDRESS 0x68
#define ALTIMETER_ADDRESS 0x60

//pefroms a quick check to verify the i2c bus is working and both sensors are responding.
sensors_init();

//reads the IMU data
sensors_read_imu(uint8_t[12] data);//This is probably going to be an array. I'll need to look into the syntax

//read the altimeter data
sensors_read_altimeter(uint8_t data);
