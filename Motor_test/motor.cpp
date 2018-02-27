#include "motor.h"
#include "Arduino.h"

motor::motor(int pinIDNum) {
  ID = pinIDNum;
  speed = 0;
}

void motor::arm() {
  if (speed == 0)
    changeSpeed(10);
}

void motor::disarm() {
  if (speed > 0)
    changeSpeed(0);
}

void motor::changeSpeed(int newSpeed) {
  analogWrite(ID, newSpeed);
  speed = newSpeed;
}
