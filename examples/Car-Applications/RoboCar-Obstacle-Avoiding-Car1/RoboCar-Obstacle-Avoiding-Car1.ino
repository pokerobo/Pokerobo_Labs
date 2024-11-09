#include "Pokerobo_Car.h"

RoboCarHandler roboCarHandler;
UltrasonicReaderByNewPing sonar(A2, A3);

int distance = 0;

void setup() {
  Serial.begin(57600);
  sonar.begin();
  roboCarHandler.turnOn();
}

void loop() {
  distance = sonar.distance_cm();
  if(distance <= 15) {
    roboCarHandler.stop();
    delay(100);
    return;
  }
  roboCarHandler.move(1, 150, 150, 1);
  delay(500);
}
