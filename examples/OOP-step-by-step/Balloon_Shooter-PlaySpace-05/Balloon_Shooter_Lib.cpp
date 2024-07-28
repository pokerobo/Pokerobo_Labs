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

int8_t DemoPlaySpace::prick(int8_t aimX, int8_t aimY) {
  int8_t count = 0;
  for (uint8_t i=0; i<_concurrentTotal; i++) {
    DemoBalloon *b = _balloons[i];
    if (b->isHit(aimX, aimY)) {
      b->_s = BALLOON_STATE::BALLOON_EXPLODED;
      count++;
    }
  }
  return count;
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
      case BALLOON_STATE::BALLOON_EXPLODED:
        this->resetBalloon(b);
        b->_s = BALLOON_STATE::BALLOON_NEW;
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
      case BALLOON_STATE::BALLOON_EXPLODED:
        this->drawExplodingBalloon(b);
        break;
    }
  }
}

void DemoPlaySpace::drawExplodingBalloon(DemoBalloon* balloon) {
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
