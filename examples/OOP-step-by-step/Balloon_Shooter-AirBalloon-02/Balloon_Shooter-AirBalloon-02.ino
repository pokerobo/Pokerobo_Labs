#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int x = 63, y = 63; int r = 5;  // balloon #1
int x2 = 80, y2 = 63, r2 = 8;   // balloon #2

void setup() {
  dh.begin();
}

void loop() {
  // balloon #1
  if (y + r >= 0) {
    y = y - 3;
  } else {
    y = 63 + r;
  }

  // balloon #2
  if (y2 + r2 >= 0) {
    y2 = y2 - 3;
  } else {
    y2 = 63 + r;
  }

  dh.firstPage();
  do {
    dh.drawCircle(x, y, r);     // balloon #1
    dh.drawCircle(x2, y2, r2);  // balloon #2
  } while(dh.nextPage());

  delay(50);
}
