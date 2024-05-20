#include <Pokerobo_RCB_master.h>
#include "Pokerobo_Lab_Aim_Target.h"
#include "Pokerobo_Lab_Air_Balloon.h"
#include "Pokerobo_Lab_Game_Balloon_Shooter.h"

GeometryDisplayHandler displayHandler(LCD_PINS_ON_RIGHT);

JoystickHandler joystickHandler;
JoystickAction action;

CoordinateAxes axes(&displayHandler);

AimTarget aimTarget(&axes);
PlaySpace playSpace(&axes, 5, 100, PLAY_SPACE_OPTION_STATUS_BAR);
GameBoard gameBoard(&axes, &aimTarget, &playSpace);

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  joystickHandler.begin();
  playSpace.begin();
}

void loop() {
  joystickHandler.input(&action);

  gameBoard.play(action.getTogglingFlags(), action.getX(), action.getY());
  gameBoard.render();

  delay(50);
}
