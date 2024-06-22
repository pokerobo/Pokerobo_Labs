#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int r = 15; int x = r; int y = 63 - r;
int speed = 3;
byte direction = 1;

void setup() {
  dh.begin();
}

void loop() {
  if (direction) {
    x = x + speed;
    if (x > 127 - r) {
      x = 127 - r;
    }
    if (x == 127 - r) {
      direction = 1 - direction;
    }
  } else {
    x = x - speed;
    if (x < r) {
      x = r;
    }
    if (x == r) {
      direction = 1 - direction;
    }
  }
  dh.firstPage();
  do {
    dh.drawCircle(x, y, r);
  } while(dh.nextPage());
  delay(50);
}
