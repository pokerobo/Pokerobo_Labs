#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Game_BalloonShooter_GunTarget.h"

class CirclePartitioning {
  public:
    CirclePartitioning(GeometryDisplayHandler* pencil);
    void draw(int8_t x, int8_t y);
  private:
    GeometryDisplayHandler* _pencil;
    int8_t _ox;
    int8_t _oy;
    int8_t _radius;
};

CirclePartitioning::CirclePartitioning(GeometryDisplayHandler* pencil) {
  if (pencil == NULL) {
    exit(0);
  }
  _pencil = pencil;
  int8_t _maxX = _pencil->getMaxX();
  int8_t _maxY = _pencil->getMaxY();
  int8_t diameter = min(_maxX, _maxY);
  _radius = (diameter >> 1) - 2;
  _ox = (diameter >> 1);
  _oy = (diameter >> 1);
}

void CirclePartitioning::draw(int8_t x, int8_t y) {
  int8_t _maxX = _pencil->getMaxX();
  int8_t _maxY = _pencil->getMaxY();
  GeometryDisplayHandler* pen = _pencil;

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
CirclePartitioning partitioning(&displayHandler);
ShootingTarget target(&displayHandler);

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
