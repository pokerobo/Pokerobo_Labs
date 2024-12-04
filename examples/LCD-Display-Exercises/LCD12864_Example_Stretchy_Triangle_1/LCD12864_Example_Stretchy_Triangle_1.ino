// Draw an equilateral triangle in the middle of the screen,
// the base of the triangle is initially a straight line connecting 
// the two points (3, 63), (123, 63); the vertex has coordinates (63, 31).

// Programmatically move the vertex of the triangle towards
// the top edge of the screen, while shrinking the base to ensure
// the area of ​​the triangle does not change.

#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int x1, y1;
int S;
int d = 0;

void setup() {
  Serial.begin(57600);
  dh.begin();
  x1 = 63; y1 = 31;
  int x2 = x1 - 60;
  int x3 = x1 + 60;
  S = (x3 - x2) * (63 - y1) / 2;
}

void draw(int S_, int x1_, int y1_) {
  int h = 63 - y1_;
  int w_2 = S / h;
  int x2_ = x1_ - w_2;
  int x3_ = x1_ + w_2;
  dh.drawTriangleOutline(x1_, y1_, x2_, 63, x3_, 63);
}

void loop() {
  if (d == 0) {
    y1 = y1 - 3;
    if (y1 < 0) {
      y1 = 0; d = 1;
    }
  } else {
    y1 = y1 + 3;
    if (y1 > 32) {
      y1 = 32; d = 0;
    }
  }
  dh.firstPage();
  do {
    draw(S, x1, y1);
  } while (dh.nextPage());
  delay(100);
}
