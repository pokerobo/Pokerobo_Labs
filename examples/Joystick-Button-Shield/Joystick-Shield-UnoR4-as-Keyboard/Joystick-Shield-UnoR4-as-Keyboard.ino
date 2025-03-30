#include "Pokerobo_RCB.h"
#include "JoystickKeyboard.h"
#include "JoystickShowInfo.h"

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

ProgramSelector programSelector(&displayHandler, &joystickHandler, SCREEN_FLOW_CONFIGURATION);

void setup() {
  Serial.begin(57600);

  joystickHandler.begin();
  displayHandler.begin();

  programSelector.add(new ArduinoUnoR4AsKeyboard());
  programSelector.add(new JoystickShowInfo(&displayHandler));

  programSelector.begin();
}

void loop() {
  programSelector.check();
}
