#include "JoystickKeyboard.h"
#include "Keyboard.h"

int ArduinoUnoR4AsKeyboard::begin() {
  return 0;
}

int ArduinoUnoR4AsKeyboard::check(void* action, void* command) {
  JoystickAction* ctrl = (JoystickAction*) action;
  if (ctrl->isButtonPressed(MASK_UP_BUTTON)) {
    Keyboard.press(KEY_UP_ARROW);
  }
  if (ctrl->isButtonClicked(MASK_UP_BUTTON)) {
    Keyboard.release(KEY_UP_ARROW);
  }

  if (ctrl->isButtonPressed(MASK_DOWN_BUTTON)) {
    Keyboard.press(KEY_DOWN_ARROW);
  }
  if (ctrl->isButtonClicked(MASK_DOWN_BUTTON)) {
    Keyboard.release(KEY_DOWN_ARROW);
  }

  if (ctrl->isButtonPressed(MASK_LEFT_BUTTON)) {
    Keyboard.press(KEY_LEFT_ARROW);
  }
  if (ctrl->isButtonClicked(MASK_LEFT_BUTTON)) {
    Keyboard.release(KEY_LEFT_ARROW);
  }

  if (ctrl->isButtonPressed(MASK_RIGHT_BUTTON)) {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
  if (ctrl->isButtonClicked(MASK_RIGHT_BUTTON)) {
    Keyboard.release(KEY_RIGHT_ARROW);
  }

  return 0;
}

int ArduinoUnoR4AsKeyboard::close() {
  return 0;
}
