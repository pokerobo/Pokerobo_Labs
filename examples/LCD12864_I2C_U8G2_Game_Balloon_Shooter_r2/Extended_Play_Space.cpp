#include <U8g2lib.h>

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
