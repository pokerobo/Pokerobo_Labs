#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);
}

void loop() {
  u8g2.firstPage();
  do {
    drawTriangleOutline(5, 5, 115, 25, 85, 55);
  } while (u8g2.nextPage());
}

void drawTriangleOutline(byte x1, byte y1, byte x2, byte y2, byte x3, byte y3) {
  u8g2.drawLine(x1, y1, x2, y2);
  u8g2.drawLine(x2, y2, x3, y3);
  u8g2.drawLine(x3, y3, x1, y1);
}
