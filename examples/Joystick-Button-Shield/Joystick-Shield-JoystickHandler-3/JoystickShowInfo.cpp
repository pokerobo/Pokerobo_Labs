#include "JoystickShowInfo.h"

void JoystickShowInfo::begin() {
  _charHeight = _pen->getMaxCharHeight();
  _charWidth = _pen->getMaxCharWidth();
  _titleX = 64 - strlen(_title)*_charWidth / 2;
}

void JoystickShowInfo::render(JoystickAction* action) {
  _pen->firstPage();
  do {
    show(action);
  } while (_pen->nextPage());
}

void JoystickShowInfo::show(JoystickAction* action) {
  _pen->drawStr(_titleX, _titleY, _title);
  showFlags(0, 32, "Press: ", action->getPressingFlags());
  showFlags(0, 32 + _charHeight, "Click: ", action->getTogglingFlags());
}

void JoystickShowInfo::showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags) {
  _pen->drawStr(x, y, label);
  _pen->drawStr(x + _charWidth*strlen(label), y, int2bin(flags));
}

char* JoystickShowInfo::int2bin(unsigned int x) {
  for (int i=0; i<16; i++) _buffer[15-i] = '0' + ((x & (1 << i)) > 0);
  _buffer[16] ='\0';
  return _buffer;
}
