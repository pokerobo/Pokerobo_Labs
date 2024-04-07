#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lib_Aim_Target.h"

const u8g2_cb_t* u8g2_rotation = U8G2_R3;

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

lcd_layout_t convertRotationToLayout(u8g2_cb_t *rotation) {
  if (rotation == U8G2_R0) return LCD_LAYOUT_R0;
  if (rotation == U8G2_R1) return LCD_LAYOUT_R1;
  if (rotation == U8G2_R2) return LCD_LAYOUT_R2;
  if (rotation == U8G2_R3) return LCD_LAYOUT_R3;
  return LCD_LAYOUT_R0;
}

JoystickHandler joystickHandler;
AimTarget target(&u8g2, convertRotationToLayout(u8g2_rotation));

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);

  joystickHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveX(target.speedOfX(action.getX(), action.getY()));
  target.moveY(target.speedOfY(action.getX(), action.getY()));

  u8g2.firstPage();
  do {
    target.render();
  } while (u8g2.nextPage());

  delay(10);
}
