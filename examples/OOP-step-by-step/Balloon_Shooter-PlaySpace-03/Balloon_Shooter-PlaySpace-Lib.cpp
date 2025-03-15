#include "Balloon_Shooter-PlaySpace-Lib.h"

DemoPlaySpace::DemoPlaySpace(GeometryDisplayHandler* pencil,
    uint8_t concurrentTotal) {
  _pencil = pencil;
  _concurrentTotal = concurrentTotal;
}

void DemoPlaySpace::begin() {
  for(int k=0; k<_concurrentTotal; k++) {
    _balloons[k] = new DemoBalloon();
    resetBalloon(_balloons[k]);
  }
}

void DemoPlaySpace::change() {
  for(int i=0; i<_concurrentTotal; i++) {
    DemoBalloon* balloon = _balloons[i];
    if (balloon->_y + balloon->_r >= 0) {
      balloon->_y = balloon->_y - 3;
    } else {
      uint8_t _maxX = _pencil->getMaxX();
      uint8_t _maxY = _pencil->getMaxY();
      balloon->_x = random(_maxX);
      balloon->_y = balloon->_r + _maxY + 1;
    }
  }
}

void DemoPlaySpace::draw() {
  for(int i=0; i<_concurrentTotal; i++) {
    drawFlyingBalloon(_balloons[i]);
  }
}

void DemoPlaySpace::drawFlyingBalloon(DemoBalloon* balloon) {
  _pencil->drawCircle(balloon->_x, balloon->_y, balloon->_r);
}

void DemoPlaySpace::resetBalloon(DemoBalloon* balloon) {
  uint8_t _maxX = _pencil->getMaxX();
  uint8_t _maxY = _pencil->getMaxY();
  balloon->_r = random(5, 10 + 1);
  balloon->_x = random(_maxX);
  balloon->_y = balloon->_r + _maxY + 1;
}
