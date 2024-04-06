#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);

  byte x1=5, y1=5, x2=115, y2=25, x3=120, y3=45, x4=85, y4=64, x5=40, y5=50;

  u8g2.firstPage();
  do {
    drawPentagonOutline(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (u8g2.nextPage());
  delay(3000);

  u8g2.firstPage();
  do {
    drawPentagonOutline(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
    drawScanningLines(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (u8g2.nextPage());
  delay(3000);

  u8g2.firstPage();
  do {
    drawPentagonConvexShape(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (u8g2.nextPage());
  delay(4000);
}

void loop() {
}

void drawPentagonOutline(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  u8g2.drawLine(x1, y1, x2, y2);
  u8g2.drawLine(x2, y2, x3, y3);
  u8g2.drawLine(x3, y3, x4, y4);
  u8g2.drawLine(x4, y4, x5, y5);
  u8g2.drawLine(x5, y5, x1, y1);
}

void drawScanningLines(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  u8g2.drawLine(x1, y1, x3, y3);
  u8g2.drawLine(x1, y1, x4, y4);
}

void drawPentagonConvexShape(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  u8g2.drawTriangle(x1, y1, x2, y2, x3, y3);
  u8g2.drawTriangle(x1, y1, x3, y3, x4, y4);
  u8g2.drawTriangle(x1, y1, x4, y4, x5, y5);
}
