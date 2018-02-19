#ifndef attitude_h
#define attitude_h

#include "attitude.h"
#include "sensor.h"
#include "motor.h"
#include <QueueArray.h>

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
    QueueArray<char> commands;
    enum attitude_SM_t {off_st, init_st, ready_st, execute_cmd_st} currentState;
    int calibration_count;

    attitude();
    void pid();
    void calibrate();
    void tick(uint16_t cmd_in);
};
#endif
