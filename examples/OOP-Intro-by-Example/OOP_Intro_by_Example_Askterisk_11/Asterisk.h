#ifndef __POKEROBO_LAB_SHAPE_ASTERISK_H__
#define __POKEROBO_LAB_SHAPE_ASTERISK_H__

#include "Pokerobo_Lab_Display_Handler.h"

typedef enum {
  VERTICAL_MIRROR = 0,
  SYMMETRICAL_MIRROR,
  HORIZONTAL_MIRROR
} mirror_direction_t;

class Asterisk {
  public:
    Asterisk(GeometryDisplayHandler* displayHandler,
        JoystickHandler* joystickHandler = NULL,
        int radius = 20);
    void followJoystick();
    void followJoystick(int joystickX, int joystickY);
    void setPosition(int screenX, int screenY);
    void setMirrorPositionOf(Asterisk* asterisk, mirror_direction_t mirror = VERTICAL_MIRROR);
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
