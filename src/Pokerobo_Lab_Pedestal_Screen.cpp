#include "Pokerobo_Lab_Pedestal_Screen.h"

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
    int8_t _charHeight = this->getMaxCharHeight();
    int8_t _charWidth = this->getMaxCharWidth();
    this->drawStr(64 + (32 - _charWidth*strlen(_title)/2), 0 + _charHeight, _title);
    for(uint8_t i=0; i<state->getTotal(); i++) {
      this->drawStr(64, 0 + _charHeight + 10 + _charHeight * i, _lines[i]);
    }
  }
}

//-------------------------------------------------------------------------------------------------

void Pedestal2DisplayHandler::prepareDisplay(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
  }
}

void Pedestal2DisplayHandler::renderInternal(JoystickAction *action, PedestalState *state) {
  if (action != NULL) {
    this->renderJoystickAction_(0, 0, action);
  }
  if (state != NULL) {
    int8_t _charHeight = this->getMaxCharHeight();
    int8_t _charWidth = this->getMaxCharWidth();
    for(uint8_t i=0; i<state->getTotal(); i++) {
      CoordinatePoint hc = getHorizontalCenterOf_(i);
      this->drawLine(hc.x - _radius - 1, hc.y, hc.x + _radius + 1, hc.y);
      this->drawCircle(hc.x, hc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint hp = getHorizontalPointOf_(i, state, &hc);
      this->drawLine(hc.x , hc.y, hp.x, hp.y);

      CoordinatePoint vc = getVerticalCenterOf_(i);
      this->drawLine(vc.x - _radius - 1, vc.y, vc.x + _radius + 1, vc.y);
      this->drawCircle(vc.x, vc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint vp = getVerticalPointOf_(i, state, &vc);
      this->drawLine(vc.x , vc.y, vp.x, vp.y);
    }
  }
}

CoordinatePoint Pedestal2DisplayHandler::getHorizontalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + _radius;
  center.y = _top + _topPad + _radius*(i + 1) + i*_verticalPad;
  return center;
}

CoordinatePoint Pedestal2DisplayHandler::getHorizontalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c, bool isBound) {
  CoordinatePoint point;
  float val = state->getHorizontalPositionOf(i);
  val = val*3.14159/180;
  point.x = c->x + (cos(val) * _radius);
  point.y = c->y - (sin(val) * _radius);
  return point;
}

CoordinatePoint Pedestal2DisplayHandler::getVerticalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + 2*_radius + _horizontalPad + _radius;
  center.y = _top + _topPad + _radius*(i + 1) + i*_verticalPad;
  return center;
}

CoordinatePoint Pedestal2DisplayHandler::getVerticalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *c, bool isBound) {
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
    char label[3] = { 'P', '-', '\n' };

    int8_t _charHeight = this->getMaxCharHeight();
    int8_t _charWidth = this->getMaxCharWidth();
    for(uint8_t i=0; i<state->getTotal(); i++) {
      CoordinatePoint hc = getHorizontalCenterOf_(i);
      this->drawLine(hc.x - _radius - 1, hc.y, hc.x + _radius + 1, hc.y);
      this->drawLine(hc.x, hc.y - 1, hc.x, hc.y + 1);
      this->drawCircle(hc.x, hc.y, _radius, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);

      CoordinatePoint maxP = getMaxPointOf_(i, &hc, state);
      CoordinatePoint minP = getMinPointOf_(i, &hc, state);
      this->drawLine(minP.x , minP.y, maxP.x, maxP.y);

      CoordinatePoint norP = getNormalPointOf_(i, &hc, state);
      this->drawCircle(norP.x , norP.y, 2);

      char line[6] = {0};
      sprintf(line, "H:%3d", state->getHorizontalPositionOf(i));
      this->drawStr(hc.x - _radius + 2, hc.y + 1*(_charHeight + 2), line);

      sprintf(line, "V:%3d", state->getVerticalPositionOf(i));
      this->drawStr(hc.x - _radius + 2, hc.y + 2*(_charHeight + 2), line);

      label[1] = '0' + i;
      this->drawStr(hc.x - _charWidth, hc.y + 3*(_charHeight + 2), label);
    }
  }
}

CoordinatePoint Pedestal3DisplayHandler::getHorizontalCenterOf_(uint8_t i) {
  CoordinatePoint center;
  center.x = _left + _leftPad + _radius + (2*_radius + _horizontalPad)*i;
  center.y = _top + _topPad + _radius;
  return center;
}

CoordinatePoint Pedestal3DisplayHandler::getMinPointOf_(uint8_t i, CoordinatePoint *c, PedestalState *state) {
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), _radius/2);
}

CoordinatePoint Pedestal3DisplayHandler::getNormalPointOf_(uint8_t i, CoordinatePoint *c, PedestalState *state) {
  int minVal = state->getVerticalMinAngleOf(i);
  int maxVal = state->getVerticalMaxAngleOf(i);
  int distance = map(state->getVerticalPositionOf(i), minVal, maxVal, _radius/2, 3*_radius/2);
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), distance);
}

CoordinatePoint Pedestal3DisplayHandler::getMaxPointOf_(uint8_t i, CoordinatePoint *c, PedestalState *state) {
  return calculatePointWithDistance_(c, state->getHorizontalPositionOf(i), 3*_radius/2);
}

CoordinatePoint Pedestal3DisplayHandler::calculatePointWithDistance_(CoordinatePoint *c, int angle, uint8_t distance) {
  CoordinatePoint point;
  float val = 3.14159*angle/180;
  point.x = gte0(c->x + (cos(val) * distance));
  point.y = gte0(c->y - (sin(val) * distance));
  return point;
}
