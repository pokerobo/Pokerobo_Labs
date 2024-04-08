#include <U8g2lib.h>
#include "Pokerobo_Lib_Water_Bubble.h"

Bubble::Bubble() {
  x = 0;
  y = 0;
  r = 10;
}

bool Bubble::isDisappeared() {
  return this->y < -this->r;
}

int8_t Bubble::getSpeed() {
  if (this->r > 8) return 4;
  if (this->r > 5) return 3;
  return 2;
}

boolean Bubble::isHit(int8_t aimX, int8_t aimY) {
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

void Bubble::explode() {
  this->y = -1 - this->r;
}

Aquarium::Aquarium(void* u8g2Ref, lcd_layout_t layout, uint8_t total) {
  _total = (total <= WATER_BUBBLES_TOTAL) ? total : WATER_BUBBLES_TOTAL;
  _u8g2Ref = u8g2Ref;
  _layout = layout;
  _maxX = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 127 : 63;
  _maxY = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 63 : 127;
}

void Aquarium::begin() {
  randomSeed(analogRead(A3));
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    b->r = random(5, 10 + 1);
    b->x = random(_maxX);
    b->y = random(b->r + _maxY + 1);
  }
}

void Aquarium::change() {
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    if (!b->isDisappeared()) {
      b->y -= b->getSpeed();
    } else {
      b->r = random(5, 10 + 1);
      b->x = random(_maxX);
      b->y = b->r + _maxY + 1;
    }
  }
}

void Aquarium::render() {
  U8G2* u8g2 = (U8G2*)_u8g2Ref;
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    u8g2->drawCircle(b->x, b->y, b->r);
  }
}

int8_t Aquarium::shoot(int8_t aimX, int8_t aimY) {
  int8_t count = 0;
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    if (b->isHit(aimX, aimY)) {
      b->explode();
      count++;
    }
  }
  return count;
}
