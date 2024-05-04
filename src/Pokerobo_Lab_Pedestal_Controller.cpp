#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Pedestal_Controller.h"

#define PEDESTAL_RANGE_X          10
#define PEDESTAL_RANGE_Y          10

#define RF24_JOYSTICK_RANGE_X     255
#define RF24_JOYSTICK_RANGE_Y     255

#define RF24_JOYSTICK_DEADZONE_X  32
#define RF24_JOYSTICK_DEADZONE_Y  32

PedestalController::PedestalController(PedestalGroup* pedestalGroup) {
  _pedestalGroup = pedestalGroup;
}

void PedestalController::begin() {}

void PedestalController::play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY) {
  uint16_t pressed = processButtonPress(toggleFlags);
  if (pressed) {
    return;
  }

  processJoystickChange(joystickX, joystickY, 'L');
}

//-------------------------------------------------------------------------------------------------

bool PedestalController::checkButtonPress(uint16_t pressed, uint16_t mask) {
  return pressed & mask;
}

uint16_t PedestalController::processButtonPress(uint16_t pressed) {
  uint16_t checked = 0;

  if(checkButtonPress(pressed, MASK_START_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "START", " is pushed");
    }
    #endif
    processStartButtonPressedEvent();
    checked |= MASK_START_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_SELECT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "SELECT", " is pushed");
    }
    #endif
    processSelectButtonPressedEvent();
    checked |= MASK_SELECT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_ANALOG_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "ANALOG", " is pushed");
    }
    #endif
    processAnalogButtonPressedEvent();
    checked |= MASK_ANALOG_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_UP_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    processDPadUpButtonPressedEvent();
    checked |= MASK_UP_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_RIGHT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    processDPadRightButtonPressedEvent();
    checked |= MASK_RIGHT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_DOWN_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    processDPadDownButtonPressedEvent();
    checked |= MASK_DOWN_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_LEFT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (_debugEnabled) {
      debugLog("JOY", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    processDPadLeftButtonPressedEvent();
    checked |= MASK_LEFT_BUTTON;
  }

  return checked;
}

int PedestalController::processJoystickChange(int nJoyX, int nJoyY, char label) {
  nJoyX = map(nJoyX, 0, 1024, -RF24_JOYSTICK_RANGE_X, RF24_JOYSTICK_RANGE_X);
  nJoyY = map(nJoyY, 0, 1024, -RF24_JOYSTICK_RANGE_Y, RF24_JOYSTICK_RANGE_Y);

  #if __DISPATCHER_RUNNING_LOG__
  if (_debugEnabled) {
    char l_[2] = { 'L', '\0' };
    debugLog("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ");
    char x_[7], y_[7];
    debugLog(" - ", "X", ": ", itoa(nJoyX, x_, 10));
    debugLog(" - ", "Y", ": ", itoa(nJoyY, y_, 10));
  }
  #endif

  if (isJoystickInDeadzone(nJoyX, nJoyY)) {
    return 0;
  }

  if (label == 'L') {
    processLeftJoystickChangeEvent(nJoyX, nJoyY);
    return 1;
  }

  if (label == 'R') {
    processRightJoystickChangeEvent(nJoyX, nJoyY);
    return 1;
  }

  #if __DISPATCHER_RUNNING_LOG__
  if (_debugEnabled) {
    char l_[2] = { 'L', '\0' };
    debugLog("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ", "not registered");
  }
  #endif

  return -1;
}

bool PedestalController::isJoystickInDeadzone(int nJoyX, int nJoyY) {
  return nJoyX <= RF24_JOYSTICK_DEADZONE_X && nJoyX >= -RF24_JOYSTICK_DEADZONE_X &&
      nJoyY <= RF24_JOYSTICK_DEADZONE_Y && nJoyY >= -RF24_JOYSTICK_DEADZONE_Y;
}

//-------------------------------------------------------------------------------------------------

void PedestalController::processStartButtonPressedEvent() {
}

void PedestalController::processSelectButtonPressedEvent() {
}

void PedestalController::processAnalogButtonPressedEvent() {
}

void PedestalController::processDPadUpButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->verticalServoUp();
  }
}

void PedestalController::processDPadRightButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->horizontalServoRight();
  }
}

void PedestalController::processDPadDownButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->verticalServoDown();
  }
}

void PedestalController::processDPadLeftButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->horizontalServoLeft();
  }
}

void PedestalController::processLeftJoystickChangeEvent(int nJoyX, int nJoyY) {
  if (_pedestalGroup != NULL) {
    nJoyX = map(nJoyX, -255, 255, PEDESTAL_RANGE_X, -PEDESTAL_RANGE_X);
    nJoyY = map(nJoyY, -255, 255, -PEDESTAL_RANGE_Y, PEDESTAL_RANGE_Y);
    _pedestalGroup->changeByJoystick(nJoyX, nJoyY);
  }
}

void PedestalController::processRightJoystickChangeEvent(int nJoyX, int nJoyY) {
}
