#include "Pokerobo_Lab_Display_Handler.h"
#include "Asterisk.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
JoystickAction joystickControl;

const int asteriskRadius = 15;

Asterisk asterisk(&displayHandler, &joystickHandler, asteriskRadius);
Asterisk asteriskMirror(&displayHandler, &joystickHandler, asteriskRadius);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  asterisk.followJoystick();
  asteriskMirror.setPosition(displayHandler.getMaxX() - asterisk.getX(), asterisk.getY());
  displayHandler.firstPage();
  do {
    asterisk.draw();
    asteriskMirror.draw();
  } while (displayHandler.nextPage());
}
