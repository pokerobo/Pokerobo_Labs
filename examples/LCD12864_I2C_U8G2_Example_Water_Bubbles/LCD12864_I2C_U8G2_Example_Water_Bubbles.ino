#include <U8g2lib.h>
#include "Pokerobo_Lib_Display_Helper.h"
#include "Pokerobo_Lib_Water_Bubble.h"

const u8g2_cb_t* u8g2_rotation = U8G2_R0;
const lcd_layout_t lcd_layout = convertRotationToLayout(u8g2_rotation);

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

PlaySpace playSpace(&u8g2, lcd_layout, 5);

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);
  playSpace.begin();
}

void loop() {
  playSpace.change();

  u8g2.firstPage();
  do {
    playSpace.render();
  } while (u8g2.nextPage());

  delay(50);
}
