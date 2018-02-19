#ifndef comms_h
#define comms_h

#include <SoftwareSerial.h>

class comms {
  public:
    SoftwareSerial* bluetooth;
    enum comm_SM_t {wait_for_cmd_st, relay_cmd_st} currentState;

    comms();
    void transmit(String input);
    void transmit(int input);
    int8_t tick();
};

#endif
