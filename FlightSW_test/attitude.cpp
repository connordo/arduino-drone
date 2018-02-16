#include "attitude.h"
#include "sensor.h"

    * *                  * *
  *     *              *     *
  *     *              *     *
    * *  *            *  * *
       *   ***********   *
         *   *


         
attitude::attitude() {
  m1 = new motor(7);
  m2 = new motor(8);
  m3 = new motor(9);
  m4 = new motor(10);
  data = new sensor();
  data.updateTelemetry();
  position_x = data.accel_x;
  position_y = data.accel_y;
}

attitude::pid() {
  //insert magic here
}