#ifndef __POKEROBO_CLI_H__
#define __POKEROBO_CLI_H__

#include <Arduino.h>

class CommandHandler {
  public:
    CommandHandler();
    int begin(HardwareSerial* serial=&Serial);
    int check();
  private:
    HardwareSerial* _serial = NULL;
    uint8_t _cmdLength = 64;
};

#endif
