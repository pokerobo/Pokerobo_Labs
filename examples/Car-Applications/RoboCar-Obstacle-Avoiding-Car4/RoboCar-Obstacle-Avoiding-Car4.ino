#include "Pokerobo_Car.h"

RoboCarHandler roboCarHandler;
UntrasonicReaderByNewPing sonar(A2, A3);

ObstacleAvoidingHandler avoidingHander(&roboCarHandler, &sonar);

void setup() {
  Serial.begin(57600);
  roboCarHandler.turnOn();
  sonar.begin();
  avoidingHander.begin();
}

void loop() {
  avoidingHander.move();
}
