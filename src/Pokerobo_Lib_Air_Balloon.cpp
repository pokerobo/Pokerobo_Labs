#include <U8g2lib.h>
#include "Pokerobo_Lib_Air_Balloon.h"

Balloon::Balloon() {
  _x = 0;
  _y = 0;
  _radius = 10;
}

int16_t Balloon::getX() {
  return this->_x;
}

int16_t Balloon::getY() {
  return this->_y;
}

int8_t Balloon::getRadius() {
  return this->_radius;
}

int8_t Balloon::getSpeed() {
  if (this->_radius > 8) return 4;
  if (this->_radius > 5) return 3;
  return 2;
}

bool Balloon::isDisappeared() {
  return this->_y < -this->_radius;
}

bool Balloon::isHit(int8_t aimX, int8_t aimY) {
  int16_t dx = abs(this->_x-aimX);
  int16_t dy = abs(this->_y-aimY);
  if (dx > this->_radius || dy > this->_radius) {
    return false;
  }
  if (dx + dy <= this->_radius) {
    return true;
  }
  if (sqrt(dx*dx + dy*dy) <= this->_radius) {
    return true;
  }
  return false;
}

void Balloon::explode() {
  this->_state = BALLOON_STATE::EXPLODED;
}

PlaySpace::PlaySpace(CoordinateAxes* axes, uint8_t total) {
  _total = (total <= CONCURRENT_BALLOONS_TOTAL) ? total : CONCURRENT_BALLOONS_TOTAL;
  _axes = axes;

  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  u8g2->setFont(u8g2_font_5x8_tf);
  _maxCharHeight = u8g2->getMaxCharHeight();
  _maxCharWidth = u8g2->getMaxCharWidth();
}

void PlaySpace::begin() {
  randomSeed(analogRead(A3));

  int8_t _maxY = _axes->getMaxY();
  int8_t minDelay = _maxY;
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    b->_state = BALLOON_STATE::NEW;
    this->initBalloon(b);
    b->_delay = random(0, _maxY);
    if (b->_delay < minDelay) {
      minDelay = b->_delay;
    }
  }
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    b->_delay -= minDelay;
  }

  this->_arisingCount = APPEARANCE_BALLOONS_TOTAL;
  this->_missingCount = 0;
  this->_destroyCount = 0;
}

void PlaySpace::initBalloon(Balloon* b) {
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  b->_radius = random(AIR_BALLOON_MIN_RADIUS, AIR_BALLOON_MAX_RADIUS + 1);
  b->_x = random(_maxX);
  b->_y = b->_radius + _maxY + 1;
  b->_delay = 0;
}

void PlaySpace::change() {
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    switch (b->_state) {
      case BALLOON_STATE::NEW:
        b->_state = BALLOON_STATE::FLYING;
      case BALLOON_STATE::FLYING:
        if (b->_delay == 0) {
          b->_delay--;
          this->_arisingCount--;
        } else if (b->_delay > 0) {
          b->_delay--;
        } else {
          b->_y -= b->getSpeed();
          if (b->isDisappeared()) {
            b->_state = BALLOON_STATE::ESCAPED;
          }
        }
        break;
      case BALLOON_STATE::EXPLODED:
        this->_destroyCount++;
        this->initBalloon(b);
        b->_state = BALLOON_STATE::NEW;
        break;
      case BALLOON_STATE::ESCAPED:
        this->_missingCount++;
        this->initBalloon(b);
        b->_state = BALLOON_STATE::NEW;
        break;
    }
  }
}

void PlaySpace::render() {
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();

  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();

  char line[15] = {};
  sprintf(line, "% 4d|% 4d% 4d",
      this->_arisingCount,
      this->_missingCount,
      this->_destroyCount);
  u8g2->drawButtonUTF8(0, _maxY, U8G2_BTN_INV|U8G2_BTN_BW0, _maxX + 1,  0,  0, line);
  u8g2->drawHLine(0, _maxY - _maxCharHeight + 1, _maxX + 1);

  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    u8g2->drawCircle(b->_x, b->_y, b->_radius);
  }
}

int8_t PlaySpace::shoot(int8_t aimX, int8_t aimY) {
  int8_t count = 0;
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    if (b->isHit(aimX, aimY)) {
      b->explode();
      count++;
    }
  }
  return count;
}
