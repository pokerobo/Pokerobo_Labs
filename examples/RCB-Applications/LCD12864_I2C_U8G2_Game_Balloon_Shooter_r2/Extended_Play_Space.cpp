#include "Extended_Play_Space.h"

void drawExplodingBall(GeometryDisplayHandler* pen, int cX, int cY, int8_t _maxX, int8_t _maxY);

void ExtendedPlaySpace::drawExplodingBalloon(Balloon* b) {
  CoordinateAxes* _axes = this->getCoordinateAxes();
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  drawExplodingBall(_axes->getPencil(), b->getX(), b->getY(), _maxX, _maxY);
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
