#include "Extended_Play_Space.h"

void drawExplodingBall(GeometryDisplayHandler* pen, int cX, int cY, int8_t _maxX, int8_t _maxY);
void stringifyInteger(uint8_t number, char* text);
int8_t estimateRewardPoint(Balloon* balloon);

void ExtendedPlaySpace::reset() {
  PlaySpace::reset();
  this->_rewardPointAmount = 0;
  this->_rewardPointTotal = 0;
}

bool ExtendedPlaySpace::hasLost() {
  return this->_rewardPointAmount < 0;
}

void ExtendedPlaySpace::onBalloonExploded(Balloon* balloon) {
  int8_t rewardPoint = estimateRewardPoint(balloon);
  this->_rewardPointTotal += rewardPoint;
  this->_rewardPointAmount += rewardPoint;
}

void ExtendedPlaySpace::onBalloonEscaped(Balloon* balloon) {
  int8_t rewardPoint = estimateRewardPoint(balloon);
  this->_rewardPointTotal += rewardPoint;
  this->_rewardPointAmount -= rewardPoint;
}

void ExtendedPlaySpace::drawExplodingBalloon(Balloon* b) {
  GeometryDisplayHandler* pen = this->getPencil();
  drawExplodingBall(pen, b->getX(), b->getY(), pen->getMaxX(), pen->getMaxY());
}

void ExtendedPlaySpace::drawFlyingBalloon(Balloon* b) {
  GeometryDisplayHandler* pen = this->getPencil();
  pen->drawCircle(b->getX(), b->getY(), b->getRadius());

  char num[3] = { 0 };
  stringifyInteger(estimateRewardPoint(b), num);

  pen->drawStr(b->getX() - (strlen(num) * getCharWidth() / 2),
      b->getY() + getCharHeight()/2, num);
}

void ExtendedPlaySpace::drawGameInfoBar() {
  GeometryDisplayHandler* pen = this->getPencil();
  int8_t _maxX = pen->getMaxX();
  int8_t _maxY = pen->getMaxY();

  this->prepareToDrawGameInfoBar();
  char line[15] = {};
  sprintf(line, "% 4d|% 4d% 4d",
      this->getRemainingBalloonTotal(),
      this->getExplodedBalloonTotal(),
      this->_rewardPointAmount);
  pen->drawButtonUTF8(0, _maxY, U8G2_BTN_INV|U8G2_BTN_BW0, _maxX + 1,  0,  0, line);
  pen->drawHLine(0, _maxY - this->getCharHeight() + 1, _maxX + 1);
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

void stringifyInteger(uint8_t number, char* text) {
  if (number <= 9) {
    text[0] = '0' + number;
    text[1] = 0;
    return;
  }
  if (number <= 99) {
    text[0] = '0' + number / 10;
    text[1] = '0' + number % 10;
    text[2] = 0;
    return;
  }
  if (number <= 255) {
    text[0] = '0' + number / 100;
    text[1] = '0' + number / 10 % 10;
    text[2] = '0' + number % 10;
    text[3] = 0;
    return;
  }
}

int8_t estimateRewardPoint(Balloon* b) {
  return b->getRadius();
}
