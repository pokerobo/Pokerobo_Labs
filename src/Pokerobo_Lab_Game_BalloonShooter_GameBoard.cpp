#include "Pokerobo_Lab_Game_BalloonShooter_GameBoard.h"

#ifndef BIT_ANALOG_BUTTON
#define BIT_ANALOG_BUTTON      6
#endif//BIT_ANALOG_BUTTON

#define MASK_ANALOG_BUTTON 1U << BIT_ANALOG_BUTTON

GameBoard::GameBoard(GeometryDisplayHandler* pencil, ShootingTarget* shootingTarget, PlaySpace* playSpace) {
  _pencil = pencil;
  initialize(shootingTarget, playSpace);
}

void GameBoard::initialize(ShootingTarget* shootingTarget, PlaySpace* playSpace) {
  _shootingTarget = shootingTarget;
  _playSpace = playSpace;
}

GeometryDisplayHandler* GameBoard::getPencil() {
  return _pencil;
}

void GameBoard::begin() {
  if (_playSpace != NULL) {
    _playSpace->begin();
  }
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

      _shootingTarget->moveX(_shootingTarget->speedOfX(joystickX, joystickY));
      _shootingTarget->moveY(_shootingTarget->speedOfY(joystickX, joystickY));

      _playSpace->prick(_shootingTarget->getX(), _shootingTarget->getY());

      _playSpace->change();

      if (_playSpace->hasLost()) {
        _state = GAME_STATE::GAME_LOSE;
        break;
      }
      if (_playSpace->isFinished()) {
        _state = GAME_STATE::GAME_WIN;
        break;
      }

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

void GameBoard::play(JoystickAction* action) {
  play(action->getTogglingFlags(), action->getX(), action->getY());
}

void GameBoard::render() {
  GeometryDisplayHandler* pen = getPencil();
  pen->firstPage();
  do {
    _playSpace->draw();
    _shootingTarget->draw();
    switch(_state) {
      case GAME_STATE::GAME_NEW:
        pen->drawStr(2, pen->getMaxY() >> 2, "  NEW GAME");
        break;
      case GAME_STATE::GAME_PLAY:
        break;
      case GAME_STATE::GAME_LOSE:
        pen->drawStr(2, pen->getMaxY() >> 2, " GAME OVER");
        break;
      case GAME_STATE::GAME_WIN:
        pen->drawStr(2, pen->getMaxY() >> 2, " YOU WIN!");
        break;
    }
  } while (pen->nextPage());
}

void GameBoard::renderAndDelay(int millis) {
  render();
  delay(millis);
}

void GameBoard::reset() {
  _playSpace->reset();
  _state = GAME_STATE::GAME_NEW;
}

bool GameBoard::isJoystickClicked(uint16_t flags) {
  return (flags & MASK_ANALOG_BUTTON) == MASK_ANALOG_BUTTON;
}
