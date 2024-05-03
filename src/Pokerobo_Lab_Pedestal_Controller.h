#ifndef __POKEROBO_LAB_PEDESTAL_CONTROLLER_H__
#define __POKEROBO_LAB_PEDESTAL_CONTROLLER_H__

#include "Pokerobo_Lab_Pedestal_Group.h"

class PedestalController {
  public:
    PedestalController(PedestalGroup* pedestalGroup);
    void begin();
    void play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY);
  protected:
    uint16_t processButtonPress(uint16_t buttons);
    int processJoystickChange(int, int, char);
  private:
    void processStartButtonPressedEvent();
    void processSelectButtonPressedEvent();
    void processAnalogButtonPressedEvent();
    void processDPadUpButtonPressedEvent();
    void processDPadRightButtonPressedEvent();
    void processDPadDownButtonPressedEvent();
    void processDPadLeftButtonPressedEvent();
    void processLeftJoystickChangeEvent(int nJoyX, int nJoyY);
    void processRightJoystickChangeEvent(int nJoyX, int nJoyY);
    bool checkButtonPress(uint16_t pressed, uint16_t mask);
    PedestalGroup* _pedestalGroup = NULL;
};

#endif
