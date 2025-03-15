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

bool DemoBalloon::isHit(int8_t aimX, int8_t aimY) {
  int dx = abs(this->_x - aimX);
  int dy = abs(this->_y - aimY);
  if (dx > this->_r || dy > this->_r) {
    return false;
  }
  if (dx + dy <= this->_r) {
    return true;
  }
  if (sqrt(dx*dx + dy*dy) <= this->_r) {
    return true;
  }
  return false;
}
