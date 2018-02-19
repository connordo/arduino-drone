#include "attitude.h"
#include "sensor.h"
#include "motor.h"

//              *  *                            *  *
//           *        *                      *        *
//          *    M1    *       Front        *    M2    *
//          *          *                    *          *
//           *        *  \                /  *        *
//              *  *      \       y+     /      *  *
//                   \   * * * * * * * * * *  /
//                    \  *                 * /
//                       *                 *
//                   x-  *                 * x+
//                       *                 *
//                       *                 *
//                    /  *                 * \
//                   /   * * * * * * * * * *  \
//              *  *       /     y-      \      *  *
//           *        *   /               \  *        *
//          *    M3    *                    *    M4    *
//          *          *                    *          *
//           *        *                      *        *
//              *  *                            *  *

attitude::attitude() {
  m1 = new motor(11);
  m2 = new motor(10);
  m3 = new motor(9);
  m4 = new motor(3);
  data = new sensor();
  data->updateTelemetry();
  position_x = data->accel_x;
  position_y = data->accel_y;
}

void attitude::pid() {
  //insert magic here
}

void attitude::tick(char cmd_in) {
  if (cmd_in) commands.push(cmd_in);

  //Moore Outputs
  switch (currentState) {
    case off_st:

      break;
    case init_st:
      m1->arm();
      m2->arm();
      m3->arm();
      m4->arm();
      data->calibrate();
      break;
    case ready_st:

      break;
    case execute_cmd_st:

      break;
  }

  //Mealy Outputs
  switch (currentState) {
    case off_st:
      if (!commands.isEmpty()) {
        if (commands.peek() == 'a') {
          commands.pop();
          currentState = init_st;
        } else {
          commands.pop();
        }
      }
      break;
    case init_st:
      currentState = ready_st;
      break;
    case ready_st:
      if (!commands.isEmpty()) {
        switch (commands.peek()) {
          case 'd':
            currentState = off_st;
            break;
        }
      }
      break;
    case execute_cmd_st:

      break;
  }
}
