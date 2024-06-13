#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Display_Handler.h"

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

class SimpleAimTarget {
  public:
    SimpleAimTarget(byte type);
    void draw();
    int8_t speedOfX(uint16_t x);
    int8_t speedOfY(uint16_t y);
    int8_t moveX(int8_t joyX);
    int8_t moveY(int8_t joyY);
  private:
    void drawPlus(int8_t x, int8_t y, int8_t d);
    byte _type;
    int8_t _x;
    int8_t _y;
};

SimpleAimTarget::SimpleAimTarget(byte type=2) {
  _type = type;
  _x = 63;
  _y = 31;
}

void SimpleAimTarget::draw() {
  switch(_type) {
    case 0:
      displayHandler.drawPixel(_x, _y);
      break;
    case 1:
      drawPlus(_x, _y, 4);
      displayHandler.drawFrame(_x-3, _y-3, 7, 7);
      break;
    case 2:
      drawPlus(_x, _y, 5);
      displayHandler.drawCircle(_x, _y, 4);
      break;
    default:
      drawPlus(_x, _y, 3);
  }
}

void SimpleAimTarget::drawPlus(int8_t x, int8_t y, int8_t d) {
  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= 127) ? x+d : 127;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= 63) ? y+d : 63;
  displayHandler.drawLine(x1, y, x2, y);
  displayHandler.drawLine(x, y1, x, y2);
}

int8_t SimpleAimTarget::speedOfX(uint16_t x) {
  int jX = -512 + x;

  Serial.print("jX: "), Serial.print(jX);
  Serial.print(" -> ");

  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int rX = map(jX, -512, 512, -5, 5);

  Serial.print("rX: "), Serial.print(rX);
  Serial.println();

  return rX;
}

int8_t SimpleAimTarget::speedOfY(uint16_t y) {
  int jY = -512 + y;

  Serial.print("jY: "), Serial.print(jY);
  Serial.print(" -> ");

  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rY = map(jY, -512, 512, 5, -5);

  Serial.print("rY: "), Serial.print(rY);
  Serial.println();

  return rY;
}

int8_t SimpleAimTarget::moveX(int8_t dX) {
  int8_t oX = _x;
  if (dX < 0 && _x < -dX) {
    _x = 0;
  } else if (dX > 0 && _x > 127 - dX) {
    _x = 127;
  } else {
    _x = _x + dX;
  }
  return _x - oX;
}

int8_t SimpleAimTarget::moveY(int8_t dY) {
  int8_t oY = _y;
  if (_y < -dY) {
    _y = 0;
  } else if (_y > 63 - dY) {
    _y = 63;
  } else {
    _y = _y + dY;
  }
  return _y - oY;
}

SimpleAimTarget target(1);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  int8_t rX = target.speedOfX(action.getX());
  int8_t rY = target.speedOfY(action.getY());

  target.moveX(rX);
  target.moveY(rY);

  displayHandler.firstPage();
  do {
    target.draw();
  } while (displayHandler.nextPage());

  delay(5);
}
