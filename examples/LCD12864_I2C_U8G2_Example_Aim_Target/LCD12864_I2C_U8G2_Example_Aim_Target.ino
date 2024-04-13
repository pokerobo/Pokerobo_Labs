#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Aim_Target.h"
#include "Pokerobo_Lab_Display_Helper.h"

const u8g2_cb_t* u8g2_rotation = U8G2_R3;
const lcd_layout_t lcd_layout = convertRotationToLayout(u8g2_rotation);

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

JoystickHandler joystickHandler;
CoordinateAxes axes(&u8g2, lcd_layout);
AimTarget target(&axes);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
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
