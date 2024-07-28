#include "Balloon_Shooter_Lib.h"

GeometryDisplayHandler dh;
DemoPlaySpace playSpace(&dh, 5);

int8_t needleX;
int8_t needleY;

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  playSpace.begin();
  needleX = dh.getDisplayWidth() / 2;
  needleY = dh.getDisplayHeight() / 2;
}

void loop() {
  playSpace.prick(needleX, needleY);

  playSpace.change();

  dh.firstPage();
  do {
    dh.drawLine(needleX, needleY, needleX, needleY - 32);
    playSpace.draw();
  } while(dh.nextPage());

  delay(50);
}
