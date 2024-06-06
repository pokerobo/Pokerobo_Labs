#ifndef __POKEROBO_LAB_SHAPE_FAN_ASTERISK_H__
#define __POKEROBO_LAB_SHAPE_FAN_ASTERISK_H__

#include "Asterisk.h"

class FanAsterisk: public Asterisk {
  public:
    FanAsterisk(GeometryDisplayHandler* displayHandler,
        JoystickHandler* joystickHandler = NULL,
        int radius = 20, int angle = 15): Asterisk(displayHandler,
            joystickHandler, radius) {
      _angle = angle;
    }
    FanAsterisk(FanAsterisk* sample): Asterisk(sample) {
      _angle = this->_angle;
    }
    void draw();
  private:
    int _angle = 15;
};

#endif
