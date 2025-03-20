#include "SimpleShootingTarget_Extension.h"

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

SimpleShootingTargetInCircle target(&displayHandler);

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
