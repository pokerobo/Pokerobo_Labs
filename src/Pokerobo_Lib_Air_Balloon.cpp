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
}

void PlaySpace::begin() {
  randomSeed(analogRead(A3));
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    b->r = random(5, 10 + 1);
    b->x = random(_maxX);
    b->y = random(b->r + _maxY + 1);
  }
}

void PlaySpace::change() {
  for (uint8_t i=0; i<_total; i++) {
    Balloon *b = &_balloons[i];
    if (!b->isDisappeared()) {
      b->y -= b->getSpeed();
    } else {
      b->r = random(5, 10 + 1);
      b->x = random(_maxX);
      b->y = b->r + _maxY + 1;
    }
  }
}

void PlaySpace::render() {
  U8G2* u8g2 = (U8G2*)_u8g2Ref;
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
      count++;
    }
  }
  return count;
}
