#include "Pokerobo_Car.h"

CarDebugLogger debugLogger;
RoboCarHandler roboCarHandler;
MovingCommand movingCommand;

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();
  roboCarHandler.setDebugLogger(&debugLogger);

  roboCarHandler.turnOn();

  // Moving forward for 1s
  movingCommand.update(255, 1, 255, 1);
  roboCarHandler.move(&movingCommand);
  delay(1000);

  roboCarHandler.stop();
}

void loop() {
}
