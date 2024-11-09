#include "Pokerobo_Car.h"

RoboCarHandler roboCarHandler;
UltrasonicReaderByNewPing sonar(A2, A3);

class MyObstacleAvoidingHandler: public ObstacleAvoidingHandler {
  public:
    using ObstacleAvoidingHandler::ObstacleAvoidingHandler;
    void move();
};

void MyObstacleAvoidingHandler::move() {
  if(willBeCollided()) {
    moveStop();
    moveBackward();

    int distanceOnLeft = lookLeft();
    int distanceOnRight = lookRight();

    if(distanceOnLeft > distanceOnRight) {
      turnLeft();
    } else {
      turnRight();
    }
  } else {
    moveForward();
  }
}

MyObstacleAvoidingHandler avoidingHander(&roboCarHandler, &sonar);

void setup() {
  Serial.begin(57600);
  roboCarHandler.turnOn();
  sonar.begin();
  avoidingHander.begin();
}

void loop() {
  avoidingHander.move();
}
