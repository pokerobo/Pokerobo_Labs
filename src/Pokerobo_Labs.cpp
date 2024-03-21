#include "Pokerobo_Labs.h"

#define MAX_NUM_ARGS 10

CommandHandler::CommandHandler() {
}

int CommandHandler::begin(HardwareSerial* serial) {
  _serial = serial;
}

bool CommandHandler::add(cmd_t* cmd) {
  if (cmd == NULL) {
    return false;
  }
  if (_numOfCmds >= cmdsTotalLimit) {
    return false;
  }
  _listOfCmds[_numOfCmds++] = cmd;
  return true;
}

int CommandHandler::check() {
  if(!_serial->available()) {
    return -1;
  }

  char line[_cmdLength];
  memset(line, 0, _cmdLength);

  readCommand(line);

  int argc;
  char* argv[MAX_NUM_ARGS] = {};

  parseCommand(line, &argc, argv);
  execCommand(argc, argv);
}

void CommandHandler::readCommand(char* line) {
  String cmdStr = _serial->readStringUntil("\n");
  cmdStr.trim();
  _serial->print("> ");
  if (cmdStr.length() < _cmdLength) {
    cmdStr.toCharArray(line, _cmdLength);
    _serial->println(line);
  } else {
    _serial->println("Too long string command");
  }
}

void CommandHandler::parseCommand(char* line, int *argc, char** argv) {
  char *ch;

  int counter = 0;
  argv[counter++] = line;

  ch = line;
  while (*ch != '\0') {
    if (*ch == ' ') {
      *ch = '\0';
      ch++;
      while (*ch == ' ') {
        ch++;
      }
      if (*ch != '\0') {
        argv[counter++] = ch;
      }
    } else {
      ch++;
    }
  }
  *argc = counter;
}

void CommandHandler::execCommand(int argc, char** argv) {
  for(int i=0; i<_numOfCmds; i++) {
    cmd_t* cmd = _listOfCmds[i];
    if (cmd != NULL) {
      if(strcmp(argv[0], cmd->name) == 0) {
        (cmd->func)(argc-1, &argv[1]);
        return;
      }
    }
  }
}
