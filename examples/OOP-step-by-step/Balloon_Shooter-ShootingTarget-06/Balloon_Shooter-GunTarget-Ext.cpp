#include "Balloon_Shooter-GunTarget-Ext.h"

void DemoSquareGunTarget::draw() {
  int x = this->getX();
  int y = this->getY();
  this->drawCross(x, y, 4);
  this->drawBound(x, y, 3);
}

void DemoSquareGunTarget::drawBound(int x, int y, int r) {
  this->getPencil()->drawFrame(x-r, y-r, 2*r + 1, 2*r + 1);
}

void DemoSquareGunTarget::drawCross(int x, int y, int d, bool straight) {
  GeometryDisplayHandler* pen = getPencil();
  int8_t _maxX = pen->getMaxX();
  int8_t _maxY = pen->getMaxY();

  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= _maxX) ? x+d : _maxX;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= _maxY) ? y+d : _maxY;

  if (straight) {
    pen->drawLine(x1, y, x2, y);
    pen->drawLine(x, y1, x, y2);
  } else {
    pen->drawLine(x1, y1, x2, y2);
    pen->drawLine(x1, y2, x2, y1);
  }
}

void DemoCircleGunTarget::drawBound(int x, int y, int r) {
  this->getPencil()->drawCircle(x, y, r);
}
