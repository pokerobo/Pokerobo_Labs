#include "Pokerobo_Lab_Display_Handler.h"
#include "Asterisk.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
JoystickAction joystickControl;

const int asteriskRadius = 15;

Asterisk asterisk(&displayHandler, &joystickHandler, asteriskRadius);
Asterisk asterisk1(&asterisk);
Asterisk asterisk2(&asterisk);
Asterisk asterisk3(&asterisk);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  asterisk.followJoystick();
  asterisk1.setMirrorPositionOf(&asterisk, VERTICAL_MIRROR);
  asterisk2.setMirrorPositionOf(&asterisk, SYMMETRICAL_MIRROR);
  asterisk3.setMirrorPositionOf(&asterisk, HORIZONTAL_MIRROR);
  displayHandler.firstPage();
  do {
    asterisk.draw();
    asterisk1.draw();
    asterisk2.draw();
    asterisk3.draw();
  } while (displayHandler.nextPage());
}
