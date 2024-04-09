#include <U8g2lib.h>
#include "Pokerobo_Lib_Air_Balloon.h"

Balloon::Balloon() {
  x = 0;
  y = 0;
  r = 10;
}

int16_t Balloon::getX() {
  return this->x;
}

int16_t Balloon::getY() {
  return this->y;
}

int8_t Balloon::getR() {
  return this->r;
}

int8_t Balloon::getSpeed() {
  if (this->r > 8) return 4;
  if (this->r > 5) return 3;
  return 2;
}

bool Balloon::isDisappeared() {
  return this->y < -this->r;
}

boolean Balloon::isHit(int8_t aimX, int8_t aimY) {
  int16_t dx = abs(x-aimX);
  int16_t dy = abs(y-aimY);
  if (dx > r || dy > r) {
    return false;
  }
  if (dx + dy <= r) {
    return true;
  }
  if (sqrt(dx*dx + dy*dy)<= r) {
    return true;
  }
  return false;
}

void Balloon::explode() {
  this->y = -1 - this->r;
}

PlaySpace::PlaySpace(void* u8g2Ref, lcd_layout_t layout, uint8_t total) {
  _total = (total <= AIR_BALLOONS_TOTAL) ? total : AIR_BALLOONS_TOTAL;
  _u8g2Ref = u8g2Ref;
  _layout = layout;

  _maxX = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 127 : 63;
  _maxY = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 63 : 127;

  U8G2* u8g2 = (U8G2*)_u8g2Ref;
  u8g2->setFont(u8g2_font_5x8_tf);
  _maxCharHeight = u8g2->getMaxCharHeight();
  _maxCharWidth = u8g2->getMaxCharWidth();
}

void PlaySpace::begin() {
  randomSeed(analogRead(A3));

  int8_t minDelay = _maxY;
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    b->r = random(AIR_BALLOON_MIN_RADIUS, AIR_BALLOON_MAX_RADIUS + 1);
    b->x = random(_maxX);
    b->y = b->r + _maxY + 1;
    b->_delay = random(0, _maxY);
    if (b->_delay < minDelay) {
      minDelay = b->_delay;
    }
  }

  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    b->_delay -= minDelay;
  }
}

void PlaySpace::change() {
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    if (b->_delay == 0) {
      b->_delay--;
      this->_arisingCount++;
    } else if (b->_delay > 0) {
      b->_delay--;
      continue;
    }
    if (!b->isDisappeared()) {
      b->y -= b->getSpeed();
    } else {
      this->_missingCount++;
      b->r = random(AIR_BALLOON_MIN_RADIUS, AIR_BALLOON_MAX_RADIUS + 1);
      b->x = random(_maxX);
      b->y = b->r + _maxY + 1;
      b->_delay = 0;
    }
  }
}

void PlaySpace::render() {
  U8G2* u8g2 = (U8G2*)_u8g2Ref;

  char line[15] = {};
  sprintf(line, "% 4d:% 4d% 4d",
      this->_arisingCount,
      this->_missingCount,
      this->_destroyCount);
  u8g2->drawButtonUTF8(0, _maxY, U8G2_BTN_INV|U8G2_BTN_BW0, _maxX + 1,  0,  0, line);
  u8g2->drawHLine(0, _maxY - _maxCharHeight + 1, _maxX + 1);

  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    u8g2->drawCircle(b->x, b->y, b->r);
  }
}

int8_t PlaySpace::shoot(int8_t aimX, int8_t aimY) {
  int8_t count = 0;
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    if (b->isHit(aimX, aimY)) {
      b->explode();
      this->_destroyCount++;
      count++;
    }
  }
  return count;
}
