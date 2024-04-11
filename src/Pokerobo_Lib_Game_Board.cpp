#include <U8g2lib.h>
#include "Pokerobo_Lib_Game_Board.h"

GameBoard::GameBoard(AimTarget* aimTarget, PlaySpace* playSpace,
    CoordinateAxes* axes) {
  _aimTarget = aimTarget;
  _playSpace = playSpace;
  _axes = axes;
}

void GameBoard::begin() {
}

void GameBoard::play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY) {
  _playSpace->change();

  _aimTarget->moveX(_aimTarget->speedOfX(joystickX, joystickY));
  _aimTarget->moveY(_aimTarget->speedOfY(joystickX, joystickY));

  _playSpace->shoot(_aimTarget->getX(), _aimTarget->getY());
}

void GameBoard::render() {
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  u8g2->firstPage();
  do {
    _playSpace->render();
    _aimTarget->render();
  } while (u8g2->nextPage());
}
