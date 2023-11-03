#ifndef __POKEROBO_CLI_H__
#define __POKEROBO_CLI_H__

#include <Arduino.h>

class CommandHandler {
  public:
    int begin();
    int check();
  private:
    uint8_t _cmdLength = 64;
};

#endif
