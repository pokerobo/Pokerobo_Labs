#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Aim_Target.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
CoordinateAxes axes(&displayHandler);
AimTarget target(&axes);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveX(target.speedOfX(action.getX(), action.getY()));
  target.moveY(target.speedOfY(action.getX(), action.getY()));

  displayHandler.firstPage();
  do {
    target.render();
  } while (displayHandler.nextPage());

  delay(10);
}
