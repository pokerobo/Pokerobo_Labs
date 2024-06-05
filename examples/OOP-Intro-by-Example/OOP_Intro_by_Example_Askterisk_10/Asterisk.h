#ifndef __POKEROBO_LAB_SHAPE_ASTERISK_H__
#define __POKEROBO_LAB_SHAPE_ASTERISK_H__

#include "Pokerobo_Lab_Display_Handler.h"

class Asterisk {
  public:
    Asterisk(GeometryDisplayHandler* displayHandler,
        JoystickHandler* joystickHandler = NULL,
        int radius = 20);
    void followJoystick();
    void followJoystick(int joystickX, int joystickY);
    void setPosition(int screenX, int screenY);
    int getX();
    int getY();
    void draw();
  private:
    JoystickHandler* _joystickHandler;
    GeometryDisplayHandler* _displayHandler;
    int radius = 20;
    int x = 0;
    int y = 0;
};

#endif
