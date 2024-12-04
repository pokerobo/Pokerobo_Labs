#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int x1, y1;
int S;
int d = 0;

void setup() {
  randomSeed(analogRead(A3));

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
  int x2_ = 63 - w_2;
  int x3_ = 63 + w_2;
  dh.drawTriangle(x1_, y1_, x2_, 63, x3_, 63);
}

void loop() {
  x1 = x1 + (3 - random(0, 6));
  if (x1 < 0) x1 = 0;
  if (x1 > 127) x1 = 127;

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
