#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int r = 15; int x = r; int y = 63 - r;
int speed = 3;
byte direction = 1;

void setup() {
  dh.begin();
}

void loop() {
  if (direction > 0) { // left-to-right direction
    x = x + speed;
    if (x + r > 127) {
      x = 127 - r;
    }
    if (x == 127 - r) {
      direction = 1 - direction; // switch to right-to-left
    }
  } else { // right-to-left direction
    x = x - speed;
    if (x < r) {
      x = r;
    }
    if (x == r) {
      direction = 1 - direction; // switch to left-to-right
    }
  }
  dh.firstPage();
  do {
    dh.drawCircle(x, y, r);
  } while(dh.nextPage());
  delay(50);
}
