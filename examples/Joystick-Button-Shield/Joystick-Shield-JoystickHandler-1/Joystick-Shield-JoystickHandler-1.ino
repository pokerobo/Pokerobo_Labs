#include "Pokerobo_Lab_Display_Handler.h"

JoystickAction joystickAction;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

u8g2_uint_t titleX = 0;
u8g2_uint_t titleY = 15;
static char title[] = "BUTTONs";
static char buffer[17];

char* int2bin(unsigned int x) {
  for (int i=0; i<16; i++) buffer[15-i] = '0' + ((x & (1 << i)) > 0);
  buffer[16] ='\0';
  return buffer;
}

u8g2_uint_t charHeight = 0;
u8g2_uint_t charWidth = 0;

void showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags) {
  displayHandler.drawStr(x, y, label);
  displayHandler.drawStr(x + charWidth*strlen(label), y, int2bin(flags));
}

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();

  charHeight = displayHandler.getMaxCharHeight();
  charWidth = displayHandler.getMaxCharWidth();
  titleX = 64 - strlen(title)*charWidth / 2;
}

void loop() {
  joystickHandler.input(&joystickAction);

  displayHandler.firstPage();
  do {
    displayHandler.drawStr(titleX, titleY, title);
    showFlags(0, 32, "Press: ", joystickAction.getPressingFlags());
    showFlags(0, 32 + charHeight, "Click: ", joystickAction.getTogglingFlags());
  } while (displayHandler.nextPage());

  delay(50);
}
