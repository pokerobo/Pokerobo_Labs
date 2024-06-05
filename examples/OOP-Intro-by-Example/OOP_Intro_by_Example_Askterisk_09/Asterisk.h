#ifndef __POKEROBO_LAB_SHAPE_ASTERISK_H__
#define __POKEROBO_LAB_SHAPE_ASTERISK_H__

#include "Pokerobo_Lab_Display_Handler.h"

int gt0(int v) {
  return (v > 0) ? v : 0;
}

class Asterisk {
  public:
    Asterisk(GeometryDisplayHandler* displayHandler,
        JoystickHandler* joystickHandler,
        int radius = 20) {
      _joystickHandler = joystickHandler;
      _displayHandler = displayHandler;
      this->radius = radius;
    }
    void followJoystick() {
      if (_joystickHandler == NULL) {
        return;
      }
      JoystickAction joystickControl;
      _joystickHandler->input(&joystickControl);
      followJoystick(joystickControl.getX(), joystickControl.getY());
    }
    void followJoystick(int joystickX, int joystickY) {
      x = map(joystickX, 0, 1023, 0, 127);
      y = map(joystickY, 0, 1023, 63,  0);
    }
    void setPosition(int screenX, int screenY) {
      x = screenX;
      y = screenY;
    }
    int getX() {
      return x;
    }
    int getY() {
      return y;
    }
    void draw() {
      _displayHandler->drawLine(x, gt0(y - radius), x, y + radius);
      _displayHandler->drawLine(gt0(x - radius), y, x + radius, y);

      int len2 = radius / sqrt(2);
      int cutx = min(len2, x);
      int cuty = min(len2, y);
      int cutz = min(cutx, cuty);

      _displayHandler->drawLine(x - cutz, y - cutz, x + len2, y + len2);
      _displayHandler->drawLine(x - cutx, y + cutx, x + cuty, y - cuty);
    }
  private:
    JoystickHandler* _joystickHandler;
    GeometryDisplayHandler* _displayHandler;
    int radius = 20;
    int x = 0;
    int y = 0;
};

#endif
