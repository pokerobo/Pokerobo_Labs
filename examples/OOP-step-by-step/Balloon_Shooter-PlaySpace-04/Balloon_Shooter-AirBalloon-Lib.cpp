#include "Balloon_Shooter-AirBalloon-Lib.h"

DemoBalloon::DemoBalloon() {}

DemoBalloon::DemoBalloon(int cx, int cy, int cr) {
  _x = cx; _y = cy; _r = cr;
}

int DemoBalloon::getX() {
  return this->_x;
}

int DemoBalloon::getY() {
  return this->_y;
}

int8_t DemoBalloon::getRadius() {
  return this->_r;
}

int8_t DemoBalloon::getSpeed() {
  if (this->_r > 8) return 4;
  if (this->_r > 5) return 3;
  return 2;
}

bool DemoBalloon::isEscaped() {
  return this->_y + this->_r < 0;
}
