#include <U8g2lib.h>
#include "Pokerobo_Lab_Game_Balloon_Shooter.h"

#ifndef BIT_ANALOG_BUTTON
#define BIT_ANALOG_BUTTON      6
#endif//BIT_ANALOG_BUTTON

#define MASK_ANALOG_BUTTON 1U << BIT_ANALOG_BUTTON

GameBoard::GameBoard(CoordinateAxes* axes, AimTarget* aimTarget, PlaySpace* playSpace) {
  _axes = axes;
  _aimTarget = aimTarget;
  _playSpace = playSpace;
}

void GameBoard::begin() {
}

void GameBoard::play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY) {
  switch(_state) {
    case GAME_STATE::GAME_NEW:
      if (toggleFlags) {
        _state = GAME_STATE::GAME_PLAY;
      }
      break;
    case GAME_STATE::GAME_PLAY:
      if (isJoystickClicked(toggleFlags)) {
        _suspending = !(_suspending);
      }
      if (_suspending) {
        return;
      }

      if (_playSpace->hasLost()) {
        _state = GAME_STATE::GAME_LOSE;
        break;
      }
      if (_playSpace->isFinished()) {
        _state = GAME_STATE::GAME_WIN;
        break;
      }

      _playSpace->change();

      _aimTarget->moveX(_aimTarget->speedOfX(joystickX, joystickY));
      _aimTarget->moveY(_aimTarget->speedOfY(joystickX, joystickY));

      _playSpace->shoot(_aimTarget->getX(), _aimTarget->getY());
      break;
    case GAME_STATE::GAME_LOSE:
      if (isJoystickClicked(toggleFlags)) {
        this->reset();
      }
      break;
    case GAME_STATE::GAME_WIN:
      if (isJoystickClicked(toggleFlags)) {
        this->reset();
      }
      break;
  }
}

void GameBoard::render() {
  U8G2* u8g2 = (U8G2*)_axes->getU8g2Ref();
  u8g2->firstPage();
  do {
    _playSpace->render();
    _aimTarget->render();
    switch(_state) {
      case GAME_STATE::GAME_NEW:
        u8g2->drawStr(2, _axes->getMaxY() >> 2, "  NEW GAME");
        break;
      case GAME_STATE::GAME_PLAY:
        break;
      case GAME_STATE::GAME_LOSE:
        u8g2->drawStr(2, _axes->getMaxY() >> 2, " GAME OVER");
        break;
      case GAME_STATE::GAME_WIN:
        u8g2->drawStr(2, _axes->getMaxY() >> 2, " YOU WIN!");
        break;
    }
  } while (u8g2->nextPage());
}

void GameBoard::reset() {
  _playSpace->reset();
  _state = GAME_STATE::GAME_NEW;
}

bool GameBoard::isJoystickClicked(uint16_t flags) {
  return (flags & MASK_ANALOG_BUTTON) == MASK_ANALOG_BUTTON;
}