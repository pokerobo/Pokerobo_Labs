#include "Pokerobo_Lab_Game_BalloonShooter_GunTarget.h"

ShootingTarget::ShootingTarget(GeometryDisplayHandler* pencil, ShootingTargetLogger* logger) {
  _pencil = pencil;
  _logger = logger;
  initialize();
}

void ShootingTarget::initialize() {
  x = getPencil()->getMaxX() >> 1;
  y = getPencil()->getMaxY() >> 1;
}

GeometryDisplayHandler* ShootingTarget::getPencil() {
  return _pencil;
}

void ShootingTarget::draw() {
  drawCross(x, y, 3);
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

int ShootingTarget::adjustX(uint16_t x) {
  int jX = -512 + x;
  return (-SHOOTING_TARGET_DEADZONE_BOUND < jX && jX < SHOOTING_TARGET_DEADZONE_BOUND) ? 0 : jX;
}

int ShootingTarget::adjustY(uint16_t y) {
  int jY = -512 + y;
  return (-SHOOTING_TARGET_DEADZONE_BOUND < jY && jY < SHOOTING_TARGET_DEADZONE_BOUND) ? 0 : jY;
}

int8_t ShootingTarget::getStepSpeedMax() {
  return SHOOTING_TARGET_MAX_STEP_SPEED;
}

int8_t ShootingTarget::speedOfX(uint16_t x, uint16_t y) {
  int jX = this->adjustX(x);
  int jY = this->adjustY(y);
  int8_t _maxStepSpeed = this->getStepSpeedMax();

  int rX = 0;
  lcd_layout_t layout = extractLcdLayout(getPencil());
  switch (layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      rX = map(jX, -512, 512, -_maxStepSpeed, _maxStepSpeed);
      break;
    case LCD_LAYOUT_R1:
      rX = map(jY, -512, 512, -_maxStepSpeed, _maxStepSpeed);
      break;
    case LCD_LAYOUT_R3:
      rX = map(jY, -512, 512, _maxStepSpeed, -_maxStepSpeed);
      break;
  }
  if (_logger != NULL) {
    _logger->speedOfX_Log(layout, jX, jY, rX);
  }
  return rX;
}

int8_t ShootingTarget::speedOfY(uint16_t x, uint16_t y) {
  int jX = this->adjustX(x);
  int jY = this->adjustY(y);
  int8_t _maxStepSpeed = this->getStepSpeedMax();

  int rY = 0;
  lcd_layout_t layout = extractLcdLayout(getPencil());
  switch (layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      rY = map(jY, -512, 512, _maxStepSpeed, -_maxStepSpeed);
      break;
    case LCD_LAYOUT_R1:
      rY = map(jX, -512, 512, -_maxStepSpeed, _maxStepSpeed);
      break;
    case LCD_LAYOUT_R3:
      rY = map(jX, -512, 512, _maxStepSpeed, -_maxStepSpeed);
      break;
  }
  if (_logger != NULL) {
    _logger->speedOfY_Log(layout, jX, jY, rY);
  }
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

void ShootingTargetInSquare::draw() {
  int8_t x = getX();
  int8_t y = getY();
  drawCross(x, y, 4);
  getPencil()->drawFrame(x-3, y-3, 7, 7);
}

void ShootingTargetInSquare::drawCross(int8_t x, int8_t y, int8_t d, bool straight) {
  GeometryDisplayHandler* pen = getPencil();
  int8_t _maxX = pen->getMaxX();
  int8_t _maxY = pen->getMaxY();

  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int x3 = min(max(x-d + 2, 0), _maxX);

  int8_t x2 = (x+d <= _maxX) ? x+d : _maxX;
  int x4 = min(max(x+d - 2, 0), _maxX);

  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int y3 = min(max(y-d + 2, 0), _maxY);

  int8_t y2 = (y+d <= _maxY) ? y+d : _maxY;
  int y4 = min(max(y+d - 2, 0), _maxY);

  if (x3 > x1) {
    pen->drawLine(x1, y, x3, y);
  }
  if (x4 < x2) {
    pen->drawLine(x4, y, x2, y);
  }

  if (y3 > y1) {
    pen->drawLine(x, y1, x, y3);
  }
  if (y4 < y2) {
    pen->drawLine(x, y4, x, y2);
  }
}

void ShootingTargetInCircle::draw() {
  int8_t x = getX();
  int8_t y = getY();
  drawCross(x, y, 5);
  getPencil()->drawCircle(x, y, 4);
}

void VerboseShootingTargetLogger::speedOfX_Log(lcd_layout_t layout, int jX, int jY, int rX) {
  switch (layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      break;
  }
  Serial.print("rX: "), Serial.print(rX), Serial.println();
}

void VerboseShootingTargetLogger::speedOfY_Log(lcd_layout_t layout, int jX, int jY, int rY) {
  switch (layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      break;
  }
  Serial.print("rY: "), Serial.print(rY), Serial.println();
}
