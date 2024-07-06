#include "Balloon_Shooter_Lib.h"

GeometryDisplayHandler dh;

const int numOfBalls = 4;

DemoBalloon* balls[numOfBalls];

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  for(int k=0; k<numOfBalls; k++) {
    balls[k] = new DemoBalloon();
    balls[k]->init(&dh);
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
