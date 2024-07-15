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
  _r = random(5, 10 + 1);
  _y = 63 + _r;
  _x = random(0, 128);
}

void DemoBalloon::check() {
  if (_y + _r >= 0) {
    _y = _y - 3;
  } else {
    _y = 63 + _r;
    _x = random(0, 128);
  }
}

void DemoBalloon::draw() {
  _pencil->drawCircle(_x, _y, _r);  
}

DemoPlaySpace::DemoPlaySpace(GeometryDisplayHandler* pencil,
    uint8_t concurrentTotal) {
  _pencil = pencil;
  _concurrentTotal = concurrentTotal;
}

void DemoPlaySpace::begin() {
  for(int k=0; k<_concurrentTotal; k++) {
    _balloons[k] = new DemoBalloon();
    _balloons[k]->set(_pencil);
  }
}

void DemoPlaySpace::change() {
  for(int i=0; i<_concurrentTotal; i++) {
    _balloons[i]->check();
  }
}

void DemoPlaySpace::draw() {
  for(int i=0; i<_concurrentTotal; i++) {
    _balloons[i]->draw();
  }
}
