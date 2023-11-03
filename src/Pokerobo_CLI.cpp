#include "Pokerobo_CLI.h"

int CommandHandler::begin() {
}

int CommandHandler::check() {
  if(!Serial.available()) {
    return -1;
  }
	char line[_cmdLength];
	String cmdStr = Serial.readStringUntil("\n");
	Serial.print("> "), Serial.print(cmdStr);
  if (cmdStr.length() < _cmdLength) {
    cmdStr.toCharArray(line, _cmdLength);
    Serial.print("Your command: "), Serial.println(line);
  } else {
    Serial.println("Too long string command");
  }
}
