#include "Pokerobo_RCB.h"
#include "Pokerobo_Lab_JoystickAsKeyboard.h"
#include "JoystickShowInfo.h"

JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

ProgramSelector programSelector(&displayHandler, &joystickHandler, SCREEN_FLOW_CONFIGURATION);

void setup() {
  Serial.begin(57600);

  joystickHandler.begin();
  displayHandler.begin();

  #if defined(ARDUINO_UNOR4_WIFI)
  programSelector.add(new ArduinoUnoR4AsKeyboard());
  #endif
  programSelector.add(new JoystickShowInfo(&displayHandler));

  programSelector.begin();
}

void loop() {
  programSelector.check();
}
