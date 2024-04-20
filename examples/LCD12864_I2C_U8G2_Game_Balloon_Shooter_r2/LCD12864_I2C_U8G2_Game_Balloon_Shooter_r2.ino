#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Display_Helper.h"
#include "Pokerobo_Lab_Aim_Target.h"
#include "Pokerobo_Lab_Air_Balloon.h"
#include "Pokerobo_Lab_Game_Balloon_Shooter.h"

void stringifyRadius(uint8_t radius, char* text);
void drawExplodingBall(U8G2* u8g2, int cX, int cY, int8_t _maxX, int8_t _maxY);

class ExtendedPlaySpace: public PlaySpace {
  public:
    using PlaySpace::PlaySpace;
  protected:
    void drawExplodingBalloon(Balloon* b);
};

void ExtendedPlaySpace::drawExplodingBalloon(Balloon* b) {
  CoordinateAxes* _axes = this->getCoordinateAxes();
  int8_t _maxX = _axes->getMaxX();
  int8_t _maxY = _axes->getMaxY();
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  drawExplodingBall(u8g2, b->getX(), b->getY(), _maxX, _maxY);
}

const u8g2_cb_t* u8g2_rotation = U8G2_R1;
const lcd_layout_t lcd_layout = convertRotationToLayout(u8g2_rotation);

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

JoystickHandler joystickHandler;
JoystickAction action;

CoordinateAxes axes(&u8g2, lcd_layout);

AimTarget aimTarget(&axes);
ExtendedPlaySpace playSpace(&axes, 5, 100, PLAY_SPACE_OPTION_STATUS_BAR);
GameBoard gameBoard(&axes, &aimTarget, &playSpace);

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
