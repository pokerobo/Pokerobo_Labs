#include "Pokerobo_CLI.h"

CommandHandler::CommandHandler() {
}

int CommandHandler::begin(HardwareSerial* serial) {
	_serial = serial;
}

int CommandHandler::check() {
  if(!_serial->available()) {
    return -1;
  }
	char line[_cmdLength];
	String cmdStr = _serial->readStringUntil("\n");
	_serial->print("> "), _serial->print(cmdStr);
  if (cmdStr.length() < _cmdLength) {
    cmdStr.toCharArray(line, _cmdLength);
    _serial->print("Your command: "), _serial->println(line);
  } else {
    _serial->println("Too long string command");
  }
}
