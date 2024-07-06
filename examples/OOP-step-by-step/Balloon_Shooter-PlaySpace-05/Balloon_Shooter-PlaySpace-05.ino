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

  int8_t needleX = dh.getDisplayWidth() >> 1;
  int8_t needleY = dh.getDisplayHeight() >> 1;

  playSpace.prick(needleX, needleY);

  dh.firstPage();
  do {
    dh.drawLine(needleX, needleY, needleX, needleY - 32);
    playSpace.draw();
  } while(dh.nextPage());

  delay(50);
}
