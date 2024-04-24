#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
}

byte cx=64; //x center
byte cy=45; //y center
byte radius=40; //radius
byte radius2=30; //radius

void drawGauge(int x, byte y, byte r, byte r2, int v, int minVal, int maxVal) {
  u8g2.firstPage();
  do {
    u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_UPPER_RIGHT);
    u8g2.drawCircle(x, y, r2, U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_UPPER_RIGHT);
    u8g2.drawLine(cx-r, cy, cx-r2, cy);
    u8g2.drawLine(cx+r, cy, cx+r2, cy);
    u8g2.setDrawColor(1);
    u8g2.drawStr(x-30, y+15, "Value:");
    u8g2.setCursor(x+7, y+15);
    u8g2.print(v);
    float val = map(v, minVal, maxVal, 0, 180);
    val = val*3.14/180 -1.572;
    int xp = x+(sin(val) * r);
    int yp = y-(cos(val) * r);
    u8g2.drawLine(x, y, xp, yp);
    u8g2.drawLine(x-1, y-1, xp, yp);
    u8g2.drawLine(x+1, y-1, xp, yp);
    u8g2.drawLine(x-1, y, xp, yp);
    u8g2.drawLine(x+1, y, xp, yp);
  } while ( u8g2.nextPage() );
}

void loop() {
  drawGauge(cx, cy, radius, radius2, random(100), 0, 100);
  delay(500);
}
