#include "Balloon_Shooter_Lib.h"

GeometryDisplayHandler dh;
DemoPlaySpace playSpace(&dh, 5);

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  playSpace.begin();
}

void loop() {
  playSpace.change();

  dh.firstPage();
  do {
    playSpace.draw();
  } while(dh.nextPage());

  delay(50);
}
