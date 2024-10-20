#include "Pokerobo_Car.h"
#include <Servo.h>

const int RC_SPEED = 150;
const int RC_MOVING_BACKWARD_TIME = 500;
const int RC_TURN_LR_TIME = 500;
const int RC_MIN_DISTANCE_TO_OBSTACLE = 20;

RoboCarHandler roboCarHandler;
UntrasonicReaderByNewPing sonar(A2, A3);
Servo servo;

int distance = 0;

int lookLeft() {
  servo.write(90 + 70);
  delay(500);
  int distance = sonar.distance_cm();
  delay(100);
  servo.write(90);
  delay(200);
  return distance;
}

int lookRight() {
  servo.write(90 - 70);
  delay(500);
  int distance = sonar.distance_cm();
  delay(100);
  servo.write(90);
  delay(200);
  return distance;
}

void turnLeft() {
  roboCarHandler.move(-1, RC_SPEED, RC_SPEED, 1);
  delay(RC_TURN_LR_TIME);
  roboCarHandler.move(0, RC_SPEED, RC_SPEED, 0);
}

void turnRight() {
  roboCarHandler.move(1, RC_SPEED, RC_SPEED, -1);
  delay(RC_TURN_LR_TIME);
  roboCarHandler.move(0, RC_SPEED, RC_SPEED, 0);
} 

void moveForward() {
  roboCarHandler.move(1, RC_SPEED, RC_SPEED, 1);
}

void moveBackward() {
  roboCarHandler.move(-1, RC_SPEED, RC_SPEED, -1);
  delay(RC_MOVING_BACKWARD_TIME);
  roboCarHandler.move(0, RC_SPEED, RC_SPEED, 0);
}

void moveStop() {
  roboCarHandler.move(0, RC_SPEED, RC_SPEED, 0);
  delay(100);
}

void setup() {
  Serial.begin(57600);
  sonar.begin();
  roboCarHandler.turnOn();
  servo.attach(2);
  servo.write(90);
}

void loop() {
  distance = sonar.distance_cm();
  if(distance <= RC_MIN_DISTANCE_TO_OBSTACLE) {
    moveStop();
    moveBackward();

    int distanceL = lookLeft();
    int distanceR = lookRight();

    if(distanceL > distanceR) {
      turnLeft();
    } else {
      turnRight();
    }
  } else {
    moveForward();
  }
}
