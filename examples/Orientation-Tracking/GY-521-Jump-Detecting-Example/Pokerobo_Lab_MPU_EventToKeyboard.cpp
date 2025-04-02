#include "Pokerobo_Lab_MPU_EventToKeyboard.h"

#if defined(ARDUINO_UNOR4_WIFI)

#include "Keyboard.h"

void JumpingToKeyboardListener::onJumpingBegin() {
  Keyboard.press(KEY_UP_ARROW);
}

void JumpingToKeyboardListener::onJumpingEnd() {
  Keyboard.release(KEY_UP_ARROW);
}

void JumpingToKeyboardListener::onSquattingBegin() {
  Keyboard.press(KEY_DOWN_ARROW);
}

void JumpingToKeyboardListener::onSquattingEnd() {
  Keyboard.release(KEY_DOWN_ARROW);
}

#endif
