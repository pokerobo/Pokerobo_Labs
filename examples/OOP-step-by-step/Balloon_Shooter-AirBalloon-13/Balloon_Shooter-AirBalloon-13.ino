#include "Balloon_Shooter_Lib.h"

#define TOTAL_OF_BALLOONS     10

GeometryDisplayHandler dh;

int numOfBalls = TOTAL_OF_BALLOONS;

DemoBalloon* balls[TOTAL_OF_BALLOONS] = { 0 };

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  numOfBalls = random(3, TOTAL_OF_BALLOONS + 1);
  for(int k=0; k<numOfBalls; k++) {
    balls[k] = new DemoBalloon();
    balls[k]->set(&dh);
  }
}

void loop() {
  for(int i=0; i<numOfBalls; i++) {
    balls[i]->check();
  }

  dh.firstPage();
  do {
    for(int i=0; i<numOfBalls; i++) {
      balls[i]->draw();
    }
  } while(dh.nextPage());

  delay(50);
}
