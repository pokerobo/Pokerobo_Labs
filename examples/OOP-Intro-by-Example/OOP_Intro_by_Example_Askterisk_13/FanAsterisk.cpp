#include "FanAsterisk.h"

void sanitize(float rad, int x, int y, int &px, int &py) {
  int newX = px, newY = py;
  if (newX < 0) {
    newX = 0;
    int dy = tan(rad) * x;
    newY = y - dy;
  }
  if (newY < 0) {
    newY = 0;
    int dx = y / tan(rad);
    newX = x - dx;
  }
  px = newX;
  py = newY;
}

void FanAsterisk::draw() {
  for(int i=0; i<4; i++) {
    int angle = _angle + 45*i;
    while (angle >= 180) {
      angle -= 180;
    }
    float rad = angle * M_PI / 180;
    int x1 = x + radius * cos(rad);
    int y1 = y + radius * sin(rad);
    int x2 = x + x - x1;
    int y2 = y + y - y1;

    sanitize(rad, x, y, x1, y1);
    sanitize(rad, x, y, x2, y2);

    _displayHandler->drawLine(x, y, x1, y1);
    _displayHandler->drawLine(x, y, x2, y2);
  }
}
