#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Aim_Target.h"
#include "Pokerobo_Lab_Air_Balloon.h"
#include "Pokerobo_Lab_Game_Balloon_Shooter.h"
#include "Extended_Play_Space.h"

GeometryDisplayHandler displayHandler(LCD_PINS_ON_RIGHT);

JoystickHandler joystickHandler;
JoystickAction action;

AimTarget aimTarget(&displayHandler);
ExtendedPlaySpace playSpace(&displayHandler, 5, 100, PLAY_SPACE_OPTION_STATUS_BAR);
GameBoard gameBoard(&displayHandler, &aimTarget, &playSpace);

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
