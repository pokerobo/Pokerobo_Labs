#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Pedestal_Controller.h"
#include "Pokerobo_Lab_Pedestal_Screen.h"

JoystickHandler joystickHandler;
JoystickAction action;

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalGroup pedestalGroup(&pedestalHandler1,
    &pedestalHandler3);

PedestalController pedestalController(&pedestalGroup);

PedestalDisplayHandler displayHandler;

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
  displayHandler.render(&action);

  delay(20);
}
