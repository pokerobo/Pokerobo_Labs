#include "Pokerobo_Lab_Pedestal_Screen.h"
#include <U8g2lib.h>

#define gte0(x) ((x >= 0) ? x : 0)

void PedestalDisplayHandler::render(JoystickAction *action, PedestalState *state) {
  this->prepareDisplay(action, state);
  this->firstPage();
  do {
    this->renderInternal(action, state);
  } while (this->nextPage());
}

void PedestalDisplayHandler::prepareDisplay(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
    for(uint8_t i=0; i<state->getTotal(); i++) {
      sprintf(_lines[i], "%2d:%4d-%3d|", i, state->getHorizontalPositionOf(i), state->getVerticalPositionOf(i));
    }
  }
}

void PedestalDisplayHandler::renderInternal(JoystickAction *action, PedestalState *state) {
  if (action != NULL) {
    this->renderJoystickAction_(0, 0, action);
  }
  if (state != NULL) {
    U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
    int8_t _charHeight = _u8g2->getMaxCharHeight();
    int8_t _charWidth = _u8g2->getMaxCharWidth();
    _u8g2->drawStr(64 + (32 - _charWidth*strlen(_title)/2), 0 + _charHeight, _title);
    for(uint8_t i=0; i<state->getTotal(); i++) {
      _u8g2->drawStr(64, 0 + _charHeight + 10 + _charHeight * i, _lines[i]);
    }
  }
}

//-------------------------------------------------------------------------------------------------

void AdvancedDisplayHandler::prepareDisplay(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
  }
}

void AdvancedDisplayHandler::renderInternal(JoystickAction *action, PedestalState *state) {
  if (action != NULL) {
    this->renderJoystickAction_(0, 0, action);
  }
  if (state != NULL) {
    U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
    int8_t _charHeight = _u8g2->getMaxCharHeight();
    int8_t _charWidth = _u8g2->getMaxCharWidth();
    for(uint8_t i=0; i<state->getTotal(); i++) {
      CoordinatePoint hc = getHorizontalCenterOf_(i);
      _u8g2->drawLine(hc.x - _radius - 1, hc.y, hc.x + _radius + 1, hc.y);
      _u8g2->drawCircle(hc.x, hc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint hp = getHorizontalPointOf_(i, state, &hc);
      _u8g2->drawLine(hc.x , hc.y, hp.x, hp.y);

      CoordinatePoint vc = getVerticalCenterOf_(i);
      _u8g2->drawLine(vc.x - _radius - 1, vc.y, vc.x + _radius + 1, vc.y);
      _u8g2->drawCircle(vc.x, vc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint vp = getVerticalPointOf_(i, state, &vc);
      _u8g2->drawLine(vc.x , vc.y, vp.x, vp.y);
    }
  }
}

CoordinatePoint AdvancedDisplayHandler::getHorizontalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + _radius;
  center.y = _top + _topPad + _radius*(i + 1) + i*_verticalPad;
  return center;
}

CoordinatePoint AdvancedDisplayHandler::getHorizontalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c, bool isBound) {
  CoordinatePoint point;
  float val = state->getHorizontalPositionOf(i);
  val = val*3.14159/180;
  point.x = c->x + (cos(val) * _radius);
  point.y = c->y - (sin(val) * _radius);
  return point;
}

CoordinatePoint AdvancedDisplayHandler::getVerticalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + 2*_radius + _horizontalPad + _radius;
  center.y = _top + _topPad + _radius*(i + 1) + i*_verticalPad;
  return center;
}

CoordinatePoint AdvancedDisplayHandler::getVerticalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c, bool isBound) {
  CoordinatePoint point;
  float val = state->getVerticalPositionOf(i);
  val = val*3.14159/180;
  point.x = c->x - (cos(val) * _radius);
  point.y = c->y - (sin(val) * _radius);
  return point;
}

//-------------------------------------------------------------------------------------------------

void Pedestal3DisplayHandler::prepareDisplay(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
  }
}

void Pedestal3DisplayHandler::renderInternal(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
    U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
    int8_t _charHeight = _u8g2->getMaxCharHeight();
    int8_t _charWidth = _u8g2->getMaxCharWidth();
    for(uint8_t i=0; i<state->getTotal(); i++) {
      CoordinatePoint hc = getHorizontalCenterOf_(i);
      _u8g2->drawLine(hc.x - _radius - 1, hc.y, hc.x + _radius + 1, hc.y);
      _u8g2->drawLine(hc.x, hc.y - 1, hc.x, hc.y + 1);
      _u8g2->drawCircle(hc.x, hc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint maxP = getMaxPointOf_(i, state, &hc);
      CoordinatePoint minP = getMinPointOf_(i, state, &hc);
      _u8g2->drawLine(minP.x , minP.y, maxP.x, maxP.y);

      CoordinatePoint norP = getNormalPointOf_(i, state, &hc);
      _u8g2->drawCircle(norP.x , norP.y, 2);
    }
  }
}

CoordinatePoint Pedestal3DisplayHandler::getHorizontalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + _radius + (2*_radius + _horizontalPad)*i;
  center.y = _top + _topPad;
  return center;
}

CoordinatePoint Pedestal3DisplayHandler::getMinPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c) {
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), _radius/2);
}

CoordinatePoint Pedestal3DisplayHandler::getNormalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c) {
  int minVal = state->getVerticalMinAngleOf(i);
  int maxVal = state->getVerticalMaxAngleOf(i);
  int distance = map(state->getVerticalPositionOf(i), minVal, maxVal, _radius/2, 3*_radius/2);
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), distance);
}

CoordinatePoint Pedestal3DisplayHandler::getMaxPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c) {
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), 3*_radius/2);
}

CoordinatePoint Pedestal3DisplayHandler::calculatePointWithDistance_(CoordinatePoint *c, int angle, uint8_t distance) {
  CoordinatePoint point;
  float val = 3.14159*angle/180;
  point.x = gte0(c->x + (cos(val) * distance));
  point.y = gte0(c->y - (sin(val) * distance));
  return point;
}
