#ifndef __POKEROBO_LAB_GAME_BALLOON_SHOOTER_H__
#define __POKEROBO_LAB_GAME_BALLOON_SHOOTER_H__

#include "Pokerobo_Lab_Game_BalloonShooter_PlaySpace.h"
#include "Pokerobo_Lab_Game_BalloonShooter_GunTarget.h"

typedef enum GAME_STATE {
  GAME_NEW,
  GAME_PLAY,
  GAME_LOSE,
  GAME_WIN,
} game_state_t;

class GameBoard {
  public:
    GameBoard(GeometryDisplayHandler* pencil, ShootingTarget* shootingTarget, PlaySpace* playSpace);
    void begin();
    void play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY);
    void play(JoystickAction* action);
    void render();
    void renderAndDelay(int millis);
    void reset();
  protected:
    void initialize(ShootingTarget* shootingTarget, PlaySpace* playSpace);
    GeometryDisplayHandler* getPencil();
    bool isJoystickClicked(uint16_t flags);
  private:
    ShootingTarget* _shootingTarget = NULL;
    PlaySpace* _playSpace = NULL;
    GeometryDisplayHandler* _pencil = NULL;
    game_state_t _state = GAME_STATE::GAME_NEW;
    bool _suspending = false;
};

#endif
