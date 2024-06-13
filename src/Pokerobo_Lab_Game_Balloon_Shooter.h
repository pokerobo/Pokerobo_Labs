#ifndef __POKEROBO_LAB_GAME_BALLOON_SHOOTER_H__
#define __POKEROBO_LAB_GAME_BALLOON_SHOOTER_H__

#include "Pokerobo_Lab_Aim_Target.h"
#include "Pokerobo_Lab_Air_Balloon.h"
#include "Pokerobo_Lab_Display_Layout.h"

typedef enum GAME_STATE {
  GAME_NEW,
  GAME_PLAY,
  GAME_LOSE,
  GAME_WIN,
} game_state_t;

class GameBoard {
  public:
    GameBoard(CoordinateAxes* axes, AimTarget* aimTarget, PlaySpace* playSpace);
    GameBoard(GeometryDisplayHandler* pencil, AimTarget* aimTarget, PlaySpace* playSpace);
    void begin();
    void play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY);
    void render();
    void reset();
  protected:
    void initialize(AimTarget* aimTarget, PlaySpace* playSpace);
    GeometryDisplayHandler* getPencil();
    bool isJoystickClicked(uint16_t flags);
  private:
    AimTarget* _aimTarget;
    PlaySpace* _playSpace;
    CoordinateAxes* _axes = NULL;
    GeometryDisplayHandler* _pencil = NULL;
    game_state_t _state = GAME_STATE::GAME_NEW;
    bool _suspending = false;
};

#endif
