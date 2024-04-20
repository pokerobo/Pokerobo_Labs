#include "Extended_Play_Space.h"
#include <U8g2lib.h>

void drawExplodingBall(U8G2* u8g2, int cX, int cY, int8_t _maxX, int8_t _maxY);
void stringifyRadius(uint8_t radius, char* text);

void ExtendedPlaySpace::drawExplodingBalloon(Balloon* b) {
  CoordinateAxes* _axes = this->getCoordinateAxes();
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  drawExplodingBall(u8g2, b->getX(), b->getY(), _maxX, _maxY);
}

void ExtendedPlaySpace::drawFlyingBalloon(Balloon* b) {
  CoordinateAxes* _axes = this->getCoordinateAxes();
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  u8g2->drawCircle(b->getX(), b->getY(), b->getRadius());

  char num[3] = { 0 };
  stringifyRadius(b->getRadius(), num);

  u8g2->drawStr(b->getX() - (strlen(num) * getCharWidth() / 2),
      b->getY() + getCharHeight()/2, num);
}

int ge0(int v) {
  if (v < 0) return 0;
  return v;
}

int lte(int v, int max) {
  if (v < 0) return 0;
  if (v > max) return max;
  return v;
}

void drawExplodingBall(U8G2* u8g2, int cX, int cY, int8_t _maxX, int8_t _maxY) {
  u8g2->drawLine(cX, ge0(cY - 3), cX, ge0(cY - 3 - 3));
  u8g2->drawLine(lte(cX + 2, _maxX), ge0(cY - 2), lte(cX + 2 + 3, _maxX), ge0(cY - 2 - 3));
  u8g2->drawLine(lte(cX + 3, _maxX), ge0(cY), lte(cX + 3 + 3, _maxX), ge0(cY));
  u8g2->drawLine(lte(cX + 2, _maxX), lte(cY + 2, _maxY), lte(cX + 2 + 3, _maxX), lte(cY + 2 + 3, _maxY));
  u8g2->drawLine(cX, lte(cY + 3, _maxY), cX, lte(cY + 3 + 3, _maxY));
  u8g2->drawLine(ge0(cX - 2), lte(cY + 2, _maxY), ge0(cX - 2 - 3), lte(cY + 2 + 3, _maxY));
  u8g2->drawLine(ge0(cX - 3), ge0(cY), ge0(cX - 3 - 3), ge0(cY));
  u8g2->drawLine(ge0(cX - 2), ge0(cY - 2), ge0(cX - 2 - 3), ge0(cY - 2 - 3));
}

void stringifyRadius(uint8_t radius, char* text) {
  if (radius <= 9) {
    text[0] = '0' + radius;
    text[1] = 0;
    return;
  }
  if (radius <= 99) {
    text[0] = '0' + radius / 10;
    text[1] = '0' + radius % 10;
    text[2] = 0;
    return;
  }
  if (radius <= 255) {
    text[0] = '0' + radius / 100;
    text[1] = '0' + radius / 10 % 10;
    text[2] = '0' + radius % 10;
    text[3] = 0;
    return;
  }
}
