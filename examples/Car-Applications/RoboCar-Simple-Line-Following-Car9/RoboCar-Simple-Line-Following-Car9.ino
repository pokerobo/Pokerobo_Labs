#include "LineFollower.h"

RoboCarHandler roboCarHandler;
LineFollower lineFollower(&roboCarHandler);
LineDetector5Channels lineDetector;

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();
  roboCarHandler.turnOn();
  lineDetector.setBlackLine(true);
  lineDetector.begin();
  lineFollower.begin();
}

void loop() {
  lineFollower.check(lineDetector.read());
  delay(50);
}
