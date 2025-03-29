#include "Pokerobo_Lab_Display_Handler.h"

JoystickAction joystickAction;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

class JoystickShowInfo {
  public:
    JoystickShowInfo(GeometryDisplayHandler* pen) {
      _pen = pen;
    }
    void begin();
    void render(JoystickAction* action);
    void show(JoystickAction* action);
  protected:
    void showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags);
    char* int2bin(unsigned int x);
  private:
    GeometryDisplayHandler* _pen = NULL;
    u8g2_uint_t charHeight = 0;
    u8g2_uint_t charWidth = 0;
    char _buffer[17];
    u8g2_uint_t titleX = 0;
    u8g2_uint_t titleY = 15;
    char* title = "BUTTONs";
};

void JoystickShowInfo::begin() {
  charHeight = _pen->getMaxCharHeight();
  charWidth = _pen->getMaxCharWidth();
  titleX = 64 - strlen(title)*charWidth / 2;
}

void JoystickShowInfo::render(JoystickAction* action) {
  _pen->firstPage();
  do {
    show(action);
  } while (_pen->nextPage());
}

void JoystickShowInfo::show(JoystickAction* action) {
  _pen->drawStr(titleX, titleY, title);
  showFlags(0, 32, "Press: ", action->getPressingFlags());
  showFlags(0, 32 + charHeight, "Click: ", action->getTogglingFlags());
}

void JoystickShowInfo::showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags) {
  _pen->drawStr(x, y, label);
  _pen->drawStr(x + charWidth*strlen(label), y, int2bin(flags));
}

char* JoystickShowInfo::int2bin(unsigned int x) {
  for (int i=0; i<16; i++) _buffer[15-i] = '0' + ((x & (1 << i)) > 0);
  _buffer[16] ='\0';
  return _buffer;
}

JoystickShowInfo info(&displayHandler);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
  info.begin();
}

void loop() {
  info.render(joystickHandler.input(&joystickAction));
  delay(50);
}
