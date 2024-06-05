#include "Asterisk.h"

int gt0(int v) {
  return (v > 0) ? v : 0;
}

Asterisk::Asterisk(GeometryDisplayHandler* displayHandler,
    JoystickHandler* joystickHandler,
    int radius = 20) {
  _joystickHandler = joystickHandler;
  _displayHandler = displayHandler;
  this->radius = radius;
}

void Asterisk::followJoystick() {
  if (_joystickHandler == NULL) {
    return;
  }
  JoystickAction joystickControl;
  _joystickHandler->input(&joystickControl);
  followJoystick(joystickControl.getX(), joystickControl.getY());
}

void Asterisk::followJoystick(int joystickX, int joystickY) {
  x = map(joystickX, 0, 1023, 0, 127);
  y = map(joystickY, 0, 1023, 63,  0);
}

void Asterisk::setPosition(int screenX, int screenY) {
  x = screenX;
  y = screenY;
}

void Asterisk::setMirrorPositionOf(Asterisk* asterisk, mirror_direction_t mirror) {
  switch (mirror) {
    case VERTICAL_MIRROR:
      setPosition(_displayHandler->getMaxX() - asterisk->getX(), asterisk->getY());
      break;
    case SYMMETRICAL_MIRROR:
      setPosition(_displayHandler->getMaxX() - asterisk->getX(),
          _displayHandler->getMaxY() - asterisk->getY());
      break;
    case HORIZONTAL_MIRROR:
      setPosition(asterisk->getX(), _displayHandler->getMaxY() - asterisk->getY());
      break;
  }
}

int Asterisk::getX() {
  return x;
}

int Asterisk::getY() {
  return y;
}

void Asterisk::draw() {
  _displayHandler->drawLine(x, gt0(y - radius), x, y + radius);
  _displayHandler->drawLine(gt0(x - radius), y, x + radius, y);

  int len2 = radius / sqrt(2);
  int cutx = min(len2, x);
  int cuty = min(len2, y);
  int cutz = min(cutx, cuty);

  _displayHandler->drawLine(x - cutz, y - cutz, x + len2, y + len2);
  _displayHandler->drawLine(x - cutx, y + cutx, x + cuty, y - cuty);
}
