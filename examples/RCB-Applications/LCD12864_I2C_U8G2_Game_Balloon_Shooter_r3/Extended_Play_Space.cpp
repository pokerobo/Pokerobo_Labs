#include "Extended_Play_Space.h"

void drawExplodingBall(GeometryDisplayHandler* pen, int cX, int cY, int8_t _maxX, int8_t _maxY);
void stringifyRadius(uint8_t radius, char* text);

void ExtendedPlaySpace::drawExplodingBalloon(Balloon* b) {
  GeometryDisplayHandler* pen = this->getPencil();
  drawExplodingBall(pen, b->getX(), b->getY(), pen->getMaxX(), pen->getMaxY());
}

void ExtendedPlaySpace::drawFlyingBalloon(Balloon* b) {
  GeometryDisplayHandler* pen = this->getPencil();
  pen->drawCircle(b->getX(), b->getY(), b->getRadius());

  char num[3] = { 0 };
  stringifyRadius(b->getRadius(), num);

  pen->drawStr(b->getX() - (strlen(num) * getCharWidth() / 2),
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

void drawExplodingBall(GeometryDisplayHandler* pen, int cX, int cY, int8_t _maxX, int8_t _maxY) {
  pen->drawLine(cX, ge0(cY - 3), cX, ge0(cY - 3 - 3));
  pen->drawLine(lte(cX + 2, _maxX), ge0(cY - 2), lte(cX + 2 + 3, _maxX), ge0(cY - 2 - 3));
  pen->drawLine(lte(cX + 3, _maxX), ge0(cY), lte(cX + 3 + 3, _maxX), ge0(cY));
  pen->drawLine(lte(cX + 2, _maxX), lte(cY + 2, _maxY), lte(cX + 2 + 3, _maxX), lte(cY + 2 + 3, _maxY));
  pen->drawLine(cX, lte(cY + 3, _maxY), cX, lte(cY + 3 + 3, _maxY));
  pen->drawLine(ge0(cX - 2), lte(cY + 2, _maxY), ge0(cX - 2 - 3), lte(cY + 2 + 3, _maxY));
  pen->drawLine(ge0(cX - 3), ge0(cY), ge0(cX - 3 - 3), ge0(cY));
  pen->drawLine(ge0(cX - 2), ge0(cY - 2), ge0(cX - 2 - 3), ge0(cY - 2 - 3));
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
