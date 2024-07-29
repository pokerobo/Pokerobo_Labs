#include "Pokerobo_Lab_Game_Balloon_Shooter.h"
#include "Extended_Play_Space.h"

GeometryDisplayHandler displayHandler(LCD_PINS_ON_RIGHT);

JoystickHandler joystickHandler;
JoystickAction action;

VerboseShootingTargetLogger shootingTargetLogger;
ShootingTargetInCircle shootingTarget(&displayHandler, &shootingTargetLogger);
ExtendedPlaySpace playSpace(&displayHandler, 5, 100, PLAY_SPACE_OPTION_STATUS_BAR);
GameBoard gameBoard(&displayHandler, &shootingTarget, &playSpace);

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  joystickHandler.begin();
  gameBoard.begin();
}

void loop() {
  gameBoard.play(joystickHandler.input(&action));
  gameBoard.render();

  delay(50);
}
