// Code written by Connor Olsen

#define MOTOR_1
#define MOTOR_2
#define MOTOR_3
#define MOTOR_4


//performs a simple test to make sure the motors are running
motors_init();

//Arms the motors before flight.
motors_arm();

//disarms the motors after flight.
motors_disarm();

//changes the motor's speed.
motors_changespeed(int motor, int speed);
