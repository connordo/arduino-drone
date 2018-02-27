#ifndef motor_h
#define motor_h

class motor {
  public:
    int speed; //the current speed of the motor
    int ID; //The PWM pin assigned to the motor

    motor(int pinIDNum);
    void arm();
    void disarm();
    void changeSpeed(int newSpeed);
};
#endif
