#include "Pokerobo_Car.h"

CarDebugLogger debugLogger;
RoboCarHandler roboCarHandler;
MovingResolver movingResolver;

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();
  roboCarHandler.setDebugLogger(&debugLogger);
  roboCarHandler.set(&movingResolver);

  roboCarHandler.turnOn();

  // Moving forward for 1s
  roboCarHandler.move(0, 255);
  delay(1000);

  roboCarHandler.stop();
}

void loop() {
}
