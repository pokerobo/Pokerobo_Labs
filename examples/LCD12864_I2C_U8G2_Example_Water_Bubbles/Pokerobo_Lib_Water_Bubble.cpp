#include <U8g2lib.h>
#include "Pokerobo_Lib_Water_Bubble.h"

Bubble::Bubble() {
  x = 0;
  y = 0;
  r = 10;
}

Bubble::Bubble(int8_t _x, int8_t _y = 64+10, int8_t _r = 10) {
  x = _x;
  y = _y;
  r = _r;
}

bool Bubble::isDisappeared() {
  return this->y < -this->r;
}

int8_t Bubble::getSpeed() {
  if (this->r > 8) return 4;
  if (this->r > 5) return 3;
  return 2;
}

Aquarium::Aquarium(void* u8g2Ref, uint8_t total) {
  _total = (total <= WATER_BUBBLES_TOTAL) ? total : WATER_BUBBLES_TOTAL;
  _u8g2Ref = u8g2Ref;
}

void Aquarium::begin() {
  randomSeed(analogRead(A3));
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    b->r = random(5, 10 + 1);
    b->x = random(127);
    b->y = random(b->r + 63 + 1);
  }
}

void Aquarium::change() {
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    if (!b->isDisappeared()) {
      b->y -= b->getSpeed();
    } else {
      b->r = random(5, 10 + 1);
      b->x = random(127);
      b->y = b->r + 63 + 1;
    }
  }
}

void Aquarium::render() {
  U8G2* u8g2 = (U8G2*)_u8g2Ref;
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &_bubbles[i];
    u8g2->drawCircle(b->x, b->y, b->r, U8G2_DRAW_ALL);
  }
}