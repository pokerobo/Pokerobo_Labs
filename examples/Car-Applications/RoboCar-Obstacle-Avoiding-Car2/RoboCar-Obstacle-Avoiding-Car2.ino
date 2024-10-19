#include "Pokerobo_Car.h"
#include <Servo.h>

RoboCarHandler roboCarHandler;
UntrasonicReaderByNewPing sonar(A2, A3);
Servo servo;

int distance = 0;

int lookLeft() {
  servo.write(160); 
  delay(500);
  int distance = sonar.distance_cm();
  delay(100);
  servo.write(90);
  delay(200);
  return distance;
}

int lookRight() {
  servo.write(20); 
  delay(500);
  int distance = sonar.distance_cm();
  delay(100);
  servo.write(90);
  delay(200);
  return distance;
}

void turnLeft() {
  roboCarHandler.move(-1, 150, 150, 1);
  delay(500);
  roboCarHandler.move(0, 150, 150, 0);
}

void turnRight() {
  roboCarHandler.move(1, 150, 150, -1);
  delay(500);
  roboCarHandler.move(0, 150, 150, 0);
} 

void moveForward() {
  roboCarHandler.move(1, 150, 150, 1);
}

void moveBackward() {
  roboCarHandler.move(-1, 150, 150, -1);
  delay(500);
  roboCarHandler.move(0, 150, 150, 0);
}

void moveStop() {
  roboCarHandler.move(0, 150, 150, 0);
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
  if(distance <= 20) {
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
