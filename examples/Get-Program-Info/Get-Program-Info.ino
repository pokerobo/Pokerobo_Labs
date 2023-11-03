#include <Pokerobo_CLI.h>

CommandHandler cmdManager;

void setup() {
  Serial.begin(57600);
	cmdManager.begin();
}

void loop() {
	cmdManager.check();
	delay(100);
}
