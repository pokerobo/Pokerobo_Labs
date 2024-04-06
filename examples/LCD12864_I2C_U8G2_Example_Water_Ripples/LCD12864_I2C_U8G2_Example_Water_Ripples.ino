#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);
}

byte r0=0, r1=0, r2=0, r3=0, r4=0, r5=0;

void move(byte &x, byte &y) {
  if (x == 15) {
    y = 0;
  }
  y += 3;
  if (y >= 63) {
    y = 0;
  }
}

void loop() {
  move(r0, r1);
  move(r1, r2);
  move(r2, r3);
  move(r3, r4);
  move(r4, r5);

  u8g2.firstPage();
  do {
    u8g2.drawCircle(63, 31, r1, U8G2_DRAW_ALL);
    u8g2.drawCircle(63, 31, r2, U8G2_DRAW_ALL);
    u8g2.drawCircle(63, 31, r3, U8G2_DRAW_ALL);
    u8g2.drawCircle(63, 31, r4, U8G2_DRAW_ALL);
    u8g2.drawCircle(63, 31, r5, U8G2_DRAW_ALL);
    u8g2.drawDisc(63, 31, 10, U8G2_DRAW_ALL);
  } while (u8g2.nextPage());

  delay(300);
}
