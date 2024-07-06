#include "Balloon_Shooter_Lib.h"

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

DemoPlaySpace::DemoPlaySpace(GeometryDisplayHandler* pencil,
    uint8_t concurrentTotal) {
  _pencil = pencil;
  _concurrentTotal = concurrentTotal;
}

void DemoPlaySpace::begin() {
  for(int k=0; k<_concurrentTotal; k++) {
    _balloons[k] = new DemoBalloon();
    initBalloon(_balloons[k]);
  }
}

void DemoPlaySpace::change() {
  for(int i=0; i<_concurrentTotal; i++) {
    DemoBalloon *b = _balloons[i];
    switch (b->_s) {
      case BALLOON_STATE::BALLOON_NEW:
        b->_s = BALLOON_STATE::BALLOON_FLYING;
        break;
      case BALLOON_STATE::BALLOON_FLYING:
        b->_y -= b->getSpeed();
        if (b->isEscaped()) {
          b->_s = BALLOON_STATE::BALLOON_ESCAPED;
        }
        break;
      case BALLOON_STATE::BALLOON_ESCAPED:
        this->resetBalloon(b);
        b->_s = BALLOON_STATE::BALLOON_NEW;
        break;
    }
  }
}

void DemoPlaySpace::draw() {
  for(int i=0; i<_concurrentTotal; i++) {
    DemoBalloon *b = _balloons[i];
    switch(b->_s) {
      case BALLOON_STATE::BALLOON_FLYING:
        this->drawFlyingBalloon(b);
        break;
    }
  }
}

void DemoPlaySpace::drawFlyingBalloon(DemoBalloon* balloon) {
  _pencil->drawCircle(balloon->_x, balloon->_y, balloon->_r);
}

void DemoPlaySpace::initBalloon(DemoBalloon* balloon) {
  balloon->_s = BALLOON_STATE::BALLOON_NEW;
  this->resetBalloon(balloon);
}

void DemoPlaySpace::resetBalloon(DemoBalloon* balloon) {
  uint8_t _maxX = _pencil->getMaxX();
  uint8_t _maxY = _pencil->getMaxY();
  balloon->_r = random(5, 10 + 1);
  balloon->_x = random(_maxX);
  balloon->_y = balloon->_r + _maxY + 1;
}
