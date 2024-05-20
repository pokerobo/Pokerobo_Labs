#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Aim_Target.h"

class CirclePartitioning {
  public:
    CirclePartitioning(CoordinateAxes* axes);
    void draw(int8_t x, int8_t y);
  protected:
    CoordinateAxes* getCoordinateAxes();
  private:
    CoordinateAxes* _axes;
    int8_t _ox;
    int8_t _oy;
    int8_t _radius;
};

CirclePartitioning::CirclePartitioning(CoordinateAxes* axes) {
  _axes = axes;
  if (_axes == NULL) {
    exit(0);
  }
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  int8_t diameter = min(_maxX, _maxY);
  _radius = (diameter >> 1) - 2;
  _ox = (diameter >> 1);
  _oy = (diameter >> 1);
}

void CirclePartitioning::draw(int8_t x, int8_t y) {
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  u8g2->drawCircle(_ox, _oy, _radius);

  u8g2->drawLine(0, _oy, _maxX - 10, _oy);
  u8g2->drawLine(_ox, 0, _ox, _maxY);

  u8g2->drawLine(x, y, _ox, _oy);

  int8_t dx = abs(x - _ox);
  int8_t dy = abs(y - _oy);

  if (dx >= _radius || dy >= _radius) {
    u8g2->drawFrame(2, 2, 2*_radius + 1, 2*_radius + 1);
    u8g2->drawLine(x, y, x, _oy);
    u8g2->drawLine(x, y, _ox, y);
  } else if (dx + dy <= _radius) {
    u8g2->drawLine(_ox, 2, _ox + _radius, _oy);
    u8g2->drawLine(_ox + _radius, _oy, _ox, _oy + _radius);
    u8g2->drawLine(_ox, _oy + _radius, 2, _oy);
    u8g2->drawLine(2, _oy, _ox, 2);

    u8g2->drawLine(x, y, x, _oy);
    u8g2->drawLine(x, y, _ox, y);
  }
}

GeometryDisplayHandler displayHandler;
JoystickHandler joystickHandler;
CoordinateAxes axes(&displayHandler);
CirclePartitioning partitioning(&axes);
AimTarget target(&axes);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  Serial.begin(57600);

  joystickHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveByJoystick(action.getX(), action.getY());

  u8g2.firstPage();
  do {
    target.render();
    partitioning.draw(target.getX(), target.getY());
  } while (u8g2.nextPage());

  delay(100);
}
