#include "Pokerobo_Lab_Pedestal_Screen.h"
#include <U8g2lib.h>

void PedestalDisplayHandler::render(JoystickAction *action, PedestalState *state) {
  if (state != NULL) {
    for(uint8_t i=0; i<state->getTotal(); i++) {
      sprintf(_lines[i], "%2d:%4d-%3d|", i, state->getHorizontalPositionOf(i), state->getVerticalPositionOf(i));
      Serial.println(_lines[i]);
    }
  }
  this->firstPage();
  do {
    this->renderInternal(action, state);
  } while (this->nextPage());
}

void PedestalDisplayHandler::renderInternal(JoystickAction *action, PedestalState *state) {
  if (action != NULL) {
    this->renderJoystickAction_(0, 0, action);
  }
  if (state != NULL) {
    U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
    int8_t _charHeight = _u8g2->getMaxCharHeight();
    int8_t _charWidth = _u8g2->getMaxCharWidth();
    _u8g2->drawStr(64 + (32 - _charWidth*strlen(_title)/2), 0 + _charHeight, _title);
    for(uint8_t i=0; i<state->getTotal(); i++) {
      _u8g2->drawStr(64, 0 + _charHeight + 10 + _charHeight * i, _lines[i]);
    }
  }
}
