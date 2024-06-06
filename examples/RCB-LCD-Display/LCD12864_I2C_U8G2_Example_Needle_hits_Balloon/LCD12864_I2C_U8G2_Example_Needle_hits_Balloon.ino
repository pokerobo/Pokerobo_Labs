#include <Pokerobo_RCB.h>
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
  GeometryDisplayHandler* pen = _axes->getPencil();

  pen->drawCircle(_ox, _oy, _radius);

  pen->drawLine(0, _oy, _maxX - 10, _oy);
  pen->drawLine(_ox, 0, _ox, _maxY);

  pen->drawLine(x, y, _ox, _oy);

  int8_t dx = abs(x - _ox);
  int8_t dy = abs(y - _oy);

  if (dx >= _radius || dy >= _radius) {
    pen->drawFrame(2, 2, 2*_radius + 1, 2*_radius + 1);
    pen->drawLine(x, y, x, _oy);
    pen->drawLine(x, y, _ox, y);
  } else if (dx + dy <= _radius) {
    pen->drawLine(_ox, 2, _ox + _radius, _oy);
    pen->drawLine(_ox + _radius, _oy, _ox, _oy + _radius);
    pen->drawLine(_ox, _oy + _radius, 2, _oy);
    pen->drawLine(2, _oy, _ox, 2);

    pen->drawLine(x, y, x, _oy);
    pen->drawLine(x, y, _ox, y);
  }
}

GeometryDisplayHandler displayHandler;
JoystickHandler joystickHandler;
CoordinateAxes axes(&displayHandler);
CirclePartitioning partitioning(&axes);
AimTarget target(&axes);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();  
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveByJoystick(action.getX(), action.getY());

  displayHandler.firstPage();
  do {
    target.draw();
    partitioning.draw(target.getX(), target.getY());
  } while (displayHandler.nextPage());

  delay(100);
}
