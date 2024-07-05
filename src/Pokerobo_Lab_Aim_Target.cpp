#include "Pokerobo_Lab_Aim_Target.h"

ShootingTarget::ShootingTarget(GeometryDisplayHandler* pencil, byte type) {
  _pencil = pencil;
  initialize(type);
}

void ShootingTarget::initialize(byte type) {
  _type = type;
  x = getPencil()->getMaxX() >> 1;
  y = getPencil()->getMaxY() >> 1;
}

GeometryDisplayHandler* ShootingTarget::getPencil() {
  return _pencil;
}

void ShootingTarget::draw() {
  GeometryDisplayHandler* pen = getPencil();
  switch(_type) {
    case 0:
      pen->drawPixel(x, y);
      break;
    case 1:
      drawCross(x, y, 4);
      pen->drawFrame(x-3, y-3, 7, 7);
      break;
    case 2:
      drawCross(x, y, 5);
      pen->drawCircle(x, y, 4);
      break;
    default:
      drawCross(x, y, 3);
  }
}

void ShootingTarget::drawCross(int8_t x, int8_t y, int8_t d, bool straight) {
  GeometryDisplayHandler* pen = getPencil();
  int8_t _maxX = pen->getMaxX();
  int8_t _maxY = pen->getMaxY();

  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= _maxX) ? x+d : _maxX;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= _maxY) ? y+d : _maxY;

  if (straight) {
    pen->drawLine(x1, y, x2, y);
    pen->drawLine(x, y1, x, y2);
  } else {
    pen->drawLine(x1, y1, x2, y2);
    pen->drawLine(x1, y2, x2, y1);
  }
}

void ShootingTarget::moveByJoystick(uint16_t joystickX, uint16_t joystickY) {
  this->moveX(this->speedOfX(joystickX, joystickY));
  this->moveY(this->speedOfY(joystickX, joystickY));
}

int8_t ShootingTarget::speedOfX(uint16_t x, uint16_t y) {
  int jX = -512 + x;
  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int jY = -512 + y;
  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rX = 0;
  switch (extractLcdLayout(getPencil())) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rX = map(jX, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rX = map(jY, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rX = map(jY, -512, 512, 10, -10);
      break;
  }
  Serial.print("rX: "), Serial.print(rX), Serial.println();

  return rX;
}

int8_t ShootingTarget::speedOfY(uint16_t x, uint16_t y) {
  int jX = -512 + x;
  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int jY = -512 + y;
  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rY = 0;
  switch (extractLcdLayout(getPencil())) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rY = map(jY, -512, 512, 10, -10);
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rY = map(jX, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rY = map(jX, -512, 512, 10, -10);
      break;
  }
  Serial.print("rY: "), Serial.print(rY), Serial.println();

  return rY;
}

int8_t ShootingTarget::moveX(int8_t dX) {
  int8_t _maxX = getPencil()->getMaxX();
  if (dX < 0 && x < -dX) {
    x = 0;
  } else if (dX > 0 && x > _maxX - dX) {
    x = _maxX;
  } else {
    x = x + dX;
  }
  return x;
}

int8_t ShootingTarget::moveY(int8_t dY) {
  int8_t _maxY = getPencil()->getMaxY();
  if (y < -dY) {
    y = 0;
  } else if (y > _maxY - dY) {
    y = _maxY;
  } else {
    y = y + dY;
  }
  return y;
}

int8_t ShootingTarget::getX() {
  return x;
}

int8_t ShootingTarget::getY() {
  return y;
}
