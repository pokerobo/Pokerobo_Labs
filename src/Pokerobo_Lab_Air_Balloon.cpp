#include "Pokerobo_Lab_Air_Balloon.h"
#include "Pokerobo_Lab_Display_Handler.h"

const uint8_t* gameInfoFont = text_font_body_normal;

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

bool Balloon::isEscaped() {
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

PlaySpace::PlaySpace(GeometryDisplayHandler* pencil,
    uint8_t concurrentTotal,
    uint16_t appearanceTotal,
    uint8_t options) {
  _pencil = pencil;
  initialize(concurrentTotal, appearanceTotal, options);
}

void PlaySpace::initialize(uint8_t concurrentTotal,
    uint16_t appearanceTotal,
    uint8_t options) {
  _options = options;
  _appearanceTotal = appearanceTotal;
  _concurrentTotal = (concurrentTotal <= CONCURRENT_BALLOONS_TOTAL) ?
      concurrentTotal : CONCURRENT_BALLOONS_TOTAL;

  GeometryDisplayHandler* pen = getPencil();
  pen->setFont(gameInfoFont);
}

void PlaySpace::begin() {
  randomSeed(analogRead(A3));

  int8_t _maxY = getPencil()->getMaxY();
  int8_t minDelay = _maxY;
  for (uint8_t i=0; i<_concurrentTotal; i++) {
    Balloon *b = &_balloons[i];
    this->initBalloon(b);
    b->_delay = random(0, _maxY);
    minDelay = min(b->_delay, minDelay);
  }
  for (uint8_t i=0; i<_concurrentTotal; i++) {
    Balloon *b = &_balloons[i];
    b->_delay -= minDelay;
  }

  this->_arisingCount = this->_appearanceTotal;
  this->_missingCount = 0;
  this->_destroyCount = 0;
}

GeometryDisplayHandler* PlaySpace::getPencil() {
  return _pencil;
}

void PlaySpace::initBalloon(Balloon* b) {
  b->_state = BALLOON_STATE::BALLOON_NEW;
  resetBalloon(b);
}

void PlaySpace::resetBalloon(Balloon* b) {
  int8_t _maxX = getPencil()->getMaxX();
  int8_t _maxY = getPencil()->getMaxY();
  b->_radius = random(AIR_BALLOON_MIN_RADIUS, AIR_BALLOON_MAX_RADIUS + 1);
  b->_x = random(_maxX);
  b->_y = b->_radius + _maxY + 1;
  b->_delay = 0;
}

void PlaySpace::change() {
  for (uint8_t i=0; i<_concurrentTotal; i++) {
    Balloon *b = &_balloons[i];
    switch (b->_state) {
      case BALLOON_STATE::BALLOON_NEW:
        if (this->_arisingCount > 0) {
          this->_arisingCount--;
          b->_state = BALLOON_STATE::BALLOON_FLYING;
        }
        break;
      case BALLOON_STATE::BALLOON_FLYING:
        if (b->_delay > 0) {
          b->_delay--;
        } else {
          b->_y -= b->getSpeed();
          if (b->isEscaped()) {
            b->_state = BALLOON_STATE::BALLOON_ESCAPED;
          }
        }
        break;
      case BALLOON_STATE::BALLOON_EXPLODED:
        this->_destroyCount++;
        this->onBalloonExploded(b);
        this->resetBalloon(b);
        b->_state = BALLOON_STATE::BALLOON_NEW;
        break;
      case BALLOON_STATE::BALLOON_ESCAPED:
        this->_missingCount++;
        this->onBalloonEscaped(b);
        this->resetBalloon(b);
        b->_state = BALLOON_STATE::BALLOON_NEW;
        break;
    }
  }
}

void PlaySpace::draw() {
  if (this->_options & PLAY_SPACE_OPTION_STATUS_BAR) {
    drawGameInfoBar();
  }

  for (uint8_t i=0; i<_concurrentTotal; i++) {
    Balloon *b = &_balloons[i];
    switch(b->_state) {
      case BALLOON_STATE::BALLOON_FLYING:
        drawFlyingBalloon(b);
        break;
      case BALLOON_STATE::BALLOON_EXPLODED:
        drawExplodingBalloon(b);
        break;
    }
  }
}

int8_t PlaySpace::prick(int8_t aimX, int8_t aimY) {
  int8_t count = 0;
  for (uint8_t i=0; i<_concurrentTotal; i++) {
    Balloon *b = &_balloons[i];
    if (b->isHit(aimX, aimY)) {
      b->_state = BALLOON_STATE::BALLOON_EXPLODED;
      count++;
    }
  }
  return count;
}

bool PlaySpace::hasLost() {
  return _missingCount > 0 && _missingCount > _destroyCount;
}

bool PlaySpace::isFinished() {
  return (_missingCount + _destroyCount) == _appearanceTotal;
}

void PlaySpace::reset() {
  begin();
}

void PlaySpace::onBalloonExploded(Balloon* balloon) {
}

void PlaySpace::onBalloonEscaped(Balloon* balloon) {
}

void PlaySpace::drawExplodingBalloon(Balloon* balloon) {
}

void PlaySpace::drawFlyingBalloon(Balloon* balloon) {
  getPencil()->drawCircle(balloon->_x, balloon->_y, balloon->_radius);
}

void PlaySpace::drawGameInfoBar() {
  GeometryDisplayHandler* pen = getPencil();
  int8_t _maxX = pen->getMaxX();
  int8_t _maxY = pen->getMaxY();

  this->prepareToDrawGameInfoBar();
  char line[15] = {};
  sprintf(line, "% 4d|% 4d% 4d",
      this->getRemainingBalloonTotal(),
      this->getEscapedBalloonTotal(),
      this->getExplodedBalloonTotal());
  pen->drawButtonUTF8(0, _maxY, U8G2_BTN_INV|U8G2_BTN_BW0, _maxX + 1,  0,  0, line);
  pen->drawHLine(0, _maxY - this->getCharHeight() + 1, _maxX + 1);
}

void PlaySpace::prepareToDrawGameInfoBar() {
  getPencil()->setFont(gameInfoFont);
}

uint8_t PlaySpace::getCharHeight() {
  return getPencil()->getMaxCharHeight();
}

uint8_t PlaySpace::getCharWidth() {
  return getPencil()->getMaxCharWidth();
}

uint16_t PlaySpace::getRemainingBalloonTotal() {
  return this->_appearanceTotal - this->_missingCount - this->_destroyCount;
}

uint16_t PlaySpace::getExplodedBalloonTotal() {
  return this->_destroyCount;
}

uint16_t PlaySpace::getEscapedBalloonTotal() {
  return this->_missingCount;
}
