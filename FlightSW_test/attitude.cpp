#include "attitude.h"
#include "sensor.h"
#include "motor.h"
#include "Arduino.h"

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


/* attitude
  @description: This is a constructor for the attitude. It
  creates four instances of the motor class to represent the
  four different motors on the drone. It also creates an
  instance of sensor, which handles all the telemetry.
  initial telemetry is set, and the currentState enum of the
  state machine is initialized to 'off_st'
*/
attitude::attitude() {
  m1 = new motor(11);
  m2 = new motor(10);
  m3 = new motor(9);
  m4 = new motor(3);
  data = new sensor();
  data->updateTelemetry();
  position_x = data->accel_x;
  position_y = data->accel_y;
  currentState = off_st;
  Serial.begin(9600); //probably won't be called in the final version of the code

}

void attitude::pid() {
  //insert magic here
}

void attitude::calibrate() {

}
/* tick
    @description: this function acts as the state machine for the attitude
    control. It calls the sensor->updateTelemetry() to *hopefully
    maintain a balance. :)

    @param cmd_in: a uint16_t passed in from main, received from the comms
    state machine. Represents a command to be executed. Will probably
    be 0 during most function calls.
*/
void attitude::tick(uint16_t cmd_in) {
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
      data->calibrate(); //This, unfortunetly, Takes about 2.5 seconds
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
          currentState = init_st;
          Serial.println("STATE: init_st");
        }
        commands.pop();
      }
      break;
    case init_st:
      currentState = ready_st;
      Serial.println("STATE: ready_st");

      break;
    case ready_st:
      if (!commands.isEmpty()) {
        switch (commands.peek()) {
          case 'd':
            m1->disarm();
            m2->disarm();
            m3->disarm();
            m4->disarm();
            currentState = off_st;
            Serial.println("STATE: off_st");
            commands.pop();
            break;
          case 'u':
            m1->changeSpeed(255);
            m2->changeSpeed(255);
            m3->changeSpeed(255);
            m4->changeSpeed(255);
            commands.pop();
            break;
          default:
            commands.pop();
        }
      }
      break;
    case execute_cmd_st:

      break;
  }
}
