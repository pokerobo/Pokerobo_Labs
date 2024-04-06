#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);
}

void loop() {
  do {
    u8g2.drawLine(10, 10, 50, 50); // line #1
    u8g2.drawLine(10, 50, 100, 4); // line #2
    u8g2.drawLine(5, 32, 120, 32); // line #3
    u8g2.drawLine(64, 10, 64, 50); // line #4
  } while (u8g2.nextPage());
}
