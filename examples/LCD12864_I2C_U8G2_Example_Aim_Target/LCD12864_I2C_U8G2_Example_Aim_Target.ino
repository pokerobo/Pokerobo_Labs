#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lib_Aim_Target.h"

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

JoystickHandler joystickHandler;
AimTarget target(&u8g2);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);

  joystickHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveX(target.speedOfX(action.getX()));
  target.moveY(target.speedOfY(action.getY()));

  u8g2.firstPage();
  do {
    target.render();
  } while (u8g2.nextPage());

  delay(10);
}
