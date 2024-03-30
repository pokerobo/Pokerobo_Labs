#include <U8g2lib.h>
#include <Wire.h>

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
    u8g2.setCursor(20, 32); 
    u8g2.print("Hello world!");
  } while ( u8g2.nextPage() );   
}
