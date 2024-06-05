#include "Pokerobo_Lab_Display_Handler.h"
#include "Asterisk.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
JoystickAction joystickControl;

const int asteriskRadius = 15;

Asterisk asterisk(&displayHandler, &joystickHandler, asteriskRadius);
Asterisk asteriskR(&displayHandler, &joystickHandler, asteriskRadius);
Asterisk asteriskRB(&displayHandler, &joystickHandler, asteriskRadius);
Asterisk asteriskB(&displayHandler, &joystickHandler, asteriskRadius);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  asterisk.followJoystick();
  asteriskR.setMirrorPositionOf(&asterisk, VERTICAL_MIRROR);
  asteriskRB.setMirrorPositionOf(&asterisk, SYMMETRICAL_MIRROR);
  asteriskB.setMirrorPositionOf(&asterisk, HORIZONTAL_MIRROR);
  displayHandler.firstPage();
  do {
    asterisk.draw();
    asteriskR.draw();
    asteriskRB.draw();
    asteriskB.draw();
  } while (displayHandler.nextPage());
}
