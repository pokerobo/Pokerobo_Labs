#include "Balloon_Shooter-GunTarget-Ext.h"

JoystickAction action;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

DemoSquareGunTarget gunTarget(&displayHandler);

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  joystickHandler.begin();
}

void loop() {
  joystickHandler.input(&action);

  gunTarget.update(action.getX(), action.getY());

  displayHandler.firstPage();
  do {
    gunTarget.draw();
  } while(displayHandler.nextPage());

  delay(50);
}
