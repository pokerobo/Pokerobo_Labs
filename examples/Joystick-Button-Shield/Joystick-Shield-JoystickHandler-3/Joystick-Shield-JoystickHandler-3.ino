#include "Pokerobo_Lab_Display_Handler.h"
#include "JoystickShowInfo.h"

JoystickAction joystickAction;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

JoystickShowInfo info(&displayHandler);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
  info.begin();
}

void loop() {
  info.render(joystickHandler.input(&joystickAction));
  delay(50);
}
