#include "Balloon_Shooter_Lib.h"

DemoBalloon::DemoBalloon() {}

DemoBalloon::DemoBalloon(int cx, int cy, int cr) {
  _x = cx; _y = cy; _r = cr;
}

void DemoBalloon::init(GeometryDisplayHandler *displayHandler) {
  _r = random(5, 10 + 1);
  _x = random(0, 128);
  _y = 63;
  _pencil = displayHandler;
}

void DemoBalloon::check() {
  if (_y + _r >= 0) {
    _y = _y - 3;
  } else {
    _y = 63;
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
    _balloons[k]->init(_pencil);
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
