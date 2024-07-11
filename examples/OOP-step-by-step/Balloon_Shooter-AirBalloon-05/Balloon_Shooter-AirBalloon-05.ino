#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int x = 63, y = 63; int r = 5;
int x2 = 80, y2 = 63, r2 = 8;
int x3 = 20, y3 = 63, r3 = 13;

void check(int &cx, int &cy, int &cr) {
  if (cy + cr >= 0) {
    cy = cy - 3;
  } else {
    cy = 63 + cr;
    cx = random(0, 128);
  }
}

void draw(int cx, int cy, int cr) {
  dh.drawCircle(cx, cy, cr);
}

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
}

void loop() {
  check(x, y, r);
  check(x2, y2, r2);
  check(x3, y3, r3);

  dh.firstPage();
  do {
    draw(x, y, r);
    draw(x2, y2, r2);
    draw(x3, y3, r3);
  } while(dh.nextPage());

  delay(50);
}
