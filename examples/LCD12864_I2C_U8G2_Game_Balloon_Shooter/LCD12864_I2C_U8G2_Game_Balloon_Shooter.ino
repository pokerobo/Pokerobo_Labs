#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lib_Aim_Target.h"
#include "Pokerobo_Lib_Display_Helper.h"
#include "Pokerobo_Lib_Air_Balloon.h"
#include "Pokerobo_Lib_Game_Board.h"

const u8g2_cb_t* u8g2_rotation = U8G2_R1;
const lcd_layout_t lcd_layout = convertRotationToLayout(u8g2_rotation);

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

JoystickHandler joystickHandler;
JoystickAction action;
AimTarget aimTarget(&u8g2, lcd_layout);
PlaySpace playSpace(&u8g2, lcd_layout, 5);
GameBoard gameBoard(&aimTarget, &playSpace, &u8g2, lcd_layout);

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
  Serial.begin(57600);

  joystickHandler.begin();
  playSpace.begin();
}

void loop() {
  joystickHandler.input(&action);

  gameBoard.play(action.getTogglingFlags(), action.getX(), action.getY());
  gameBoard.render();

  delay(50);
}
