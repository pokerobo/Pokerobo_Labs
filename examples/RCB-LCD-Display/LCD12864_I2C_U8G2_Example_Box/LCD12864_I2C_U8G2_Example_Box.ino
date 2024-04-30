#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  Serial.begin(57600);
}

void loop() {
  u8g2.firstPage();
  do {
    // Hình chữ nhật (đặc)
    // bắt đầu tại tọa độ (10, 10), dài 108 pixel, cao 44 pixel
    u8g2.drawBox(10, 10, 108, 44);
  } while (u8g2.nextPage());
}