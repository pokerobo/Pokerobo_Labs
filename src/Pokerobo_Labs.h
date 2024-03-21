#ifndef __POKEROBO_LABS_H__
#define __POKEROBO_LABS_H__

#include <Arduino.h>

const uint8_t cmdsTotalLimit = 10;

typedef struct _cmd_t {
  char *name;
  void (*func)(int argc, char** argv);
  _cmd_t(char *name_, void (*func_)(int argc, char** argv)): name(name_), func(func_) {};
} cmd_t;

class CommandHandler {
  public:
    CommandHandler();
    int begin(HardwareSerial* serial=&Serial);
    bool add(cmd_t* cmd);
    int check();
  private:
    HardwareSerial* _serial = NULL;
    uint8_t _cmdLength = 64;
    uint8_t _numOfCmds = 0;
    cmd_t* _listOfCmds[cmdsTotalLimit] = {};

    void readCommand(char* line);
    void parseCommand(char* line, int *argc, char** argv);
    void execCommand(int argc, char** argv);
};

#endif
