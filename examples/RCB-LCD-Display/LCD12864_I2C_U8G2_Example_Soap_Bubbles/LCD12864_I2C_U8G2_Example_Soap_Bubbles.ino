#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Helper.h"
#include "Pokerobo_Lab_Air_Balloon.h"

const u8g2_cb_t* u8g2_rotation = U8G2_R2;
const lcd_layout_t lcd_layout = convertRotationToLayout(u8g2_rotation);

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

CoordinateAxes axes(&u8g2, lcd_layout);
PlaySpace playSpace(&axes, 5, 20, PLAY_SPACE_OPTION_STATUS_BAR);

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
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
