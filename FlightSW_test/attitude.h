#ifndef attitude_h
#define attitude_h

#include "attitude.h"
#include "sensor.h"
#include "motor.h"

class attitude {
  public:
    motor *m1;
    motor *m2;
    motor *m3;
    motor *m4;
    int position_x;
    int position_y;
    int integral_x;
    int integral_y;
    int derivative_x;
    int derivative_y;
    sensor *data;

    attitude();
    void pid();
};
#endif
