#include "Pokerobo_Car.h"

CarDebugLogger debugLogger;
RoboCarHandler roboCarHandler;

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();
  roboCarHandler.setDebugLogger(&debugLogger);

  roboCarHandler.turnOn();

  // Moving forward for 1s
  roboCarHandler.move(1, 255, 255, 1);
  delay(1000);
  // turn forward on right for 100 milliseconds
  roboCarHandler.move(1, 127, 127, 0);
  delay(100);
  // Moving forward for 1s
  roboCarHandler.move(1, 255, 255, 1);
  delay(1000);

  // Moving backward for 1s
  roboCarHandler.move(-1, 255, 255, -1);
  delay(1000);
  // turn backward on left for 100 milliseconds
  roboCarHandler.move(0, 127, 127, -1);
  delay(100);
  // Moving backward for 1s
  roboCarHandler.move(-1, 255, 255, -1);
  delay(1000);

  roboCarHandler.stop();
}

void loop() {
}
