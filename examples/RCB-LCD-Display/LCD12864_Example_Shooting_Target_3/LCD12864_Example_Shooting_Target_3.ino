#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Game_BalloonShooter_GunTarget.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
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
  } while (displayHandler.nextPage());

  delay(10);
}
