#include "Balloon_Shooter_Lib.h"

DemoBalloon::DemoBalloon() {
  init();
}

DemoBalloon::DemoBalloon(int cx, int cy, int cr) {
  _x = cx; _y = cy; _r = cr;
}

void DemoBalloon::set(GeometryDisplayHandler *displayHandler) {
  _pencil = displayHandler;
}

void DemoBalloon::init() {
  reset();
}

void DemoBalloon::reset() {
  uint8_t _maxX = _pencil->getMaxX();
  uint8_t _maxY = _pencil->getMaxY();
  _r = random(5, 10 + 1);
  _x = random(_maxX);
  _y = _r + _maxY + 1;
}

void DemoBalloon::check() {
  if (_y + _r >= 0) {
    _y = _y - 3;
  } else {
    uint8_t _maxX = _pencil->getMaxX();
    uint8_t _maxY = _pencil->getMaxY();
    _x = random(_maxX);
    _y = _r + _maxY + 1;
  }
}

void DemoBalloon::draw() {
  _pencil->drawCircle(_x, _y, _r);
}
