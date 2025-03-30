#include "Pokerobo_Lab_Display_Handler.h"

JoystickAction joystickAction;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

u8g2_uint_t _titleX = 0;
u8g2_uint_t _titleY = 15;
static char _title[] = "BUTTONs";
static char buffer[17];

char* int2bin(unsigned int x) {
  for (int i=0; i<16; i++) buffer[15-i] = '0' + ((x & (1 << i)) > 0);
  buffer[16] ='\0';
  return buffer;
}

u8g2_uint_t _charHeight = 0;
u8g2_uint_t _charWidth = 0;

void showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags) {
  displayHandler.drawStr(x, y, label);
  displayHandler.drawStr(x + _charWidth*strlen(label), y, int2bin(flags));
}

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();

  _charHeight = displayHandler.getMaxCharHeight();
  _charWidth = displayHandler.getMaxCharWidth();
  _titleX = 64 - strlen(_title)*_charWidth / 2;
}

void loop() {
  joystickHandler.input(&joystickAction);

  displayHandler.firstPage();
  do {
    displayHandler.drawStr(_titleX, _titleY, _title);
    showFlags(0, 32, "Press: ", joystickAction.getPressingFlags());
    showFlags(0, 32 + _charHeight, "Click: ", joystickAction.getTogglingFlags());
  } while (displayHandler.nextPage());

  delay(50);
}
