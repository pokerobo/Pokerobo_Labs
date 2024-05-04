#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Pedestal_Controller.h"
#include "Pokerobo_Lab_Pedestal_Screen.h"

JoystickHandler joystickHandler;
JoystickAction action;

PedestalDisplayHandler displayHandler;

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalHandler* pedestalHandlers[PEDESTALS_MAX] = {
  &pedestalHandler1,
  &pedestalHandler3,
};

PedestalGroup pedestalGroup(pedestalHandlers);
PedestalController pedestalController(&pedestalGroup);

void setup() {
  Serial.begin(57600);

  displayHandler.begin();
  joystickHandler.begin();

  pedestalGroup.begin();
  pedestalController.begin();
}

void loop() {
  joystickHandler.input(&action);
  pedestalController.play(action.getPressingFlags(), action.getX(), action.getY());
  displayHandler.render(&action);

  delay(20);
}
