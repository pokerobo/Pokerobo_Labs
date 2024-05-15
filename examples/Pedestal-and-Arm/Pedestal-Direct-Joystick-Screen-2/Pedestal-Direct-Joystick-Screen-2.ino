#include <Pokerobo_Arm.h>
#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Pedestal_Screen.h"

JoystickHandler joystickHandler;
JoystickAction action;

PedestalHandler pedestalHandler0( 0,  1);
PedestalHandler pedestalHandler1( 4,  5);
PedestalHandler pedestalHandler2( 8,  9);
PedestalHandler pedestalHandler3(14, 15);

PedestalGroup pedestalGroup(&pedestalHandler0,
    &pedestalHandler1,
    &pedestalHandler2,
    &pedestalHandler3);

PedestalController pedestalController(&pedestalGroup);

AdvancedDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);

  joystickHandler.begin();

  pedestalGroup.begin();
  pedestalController.begin();

  displayHandler.begin();
}

void loop() {
  joystickHandler.input(&action);
  pedestalController.play(action.getPressingFlags(), action.getX(), action.getY());
  displayHandler.render(&action, pedestalController.getState());

  delay(20);
}
