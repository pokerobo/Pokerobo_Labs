#ifndef __POKEROBO_LIB_GAME_BOARD_H__
#define __POKEROBO_LIB_GAME_BOARD_H__

#include "Pokerobo_Lib_Aim_Target.h"
#include "Pokerobo_Lib_Air_Balloon.h"
#include "Pokerobo_Lib_Display_Layout.h"

typedef enum GAME_STATE {
  GAME_NEW,
  GAME_PLAY,
  GAME_LOSE,
  GAME_WIN,
} game_state_t;

class GameBoard {
  public:
    GameBoard(AimTarget* aimTarget, PlaySpace* playSpace,
      CoordinateAxes* axes);
    void begin();
    void play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY);
    void render();
  private:
    AimTarget* _aimTarget;
    PlaySpace* _playSpace;
    CoordinateAxes* _axes;
    game_state_t _state = GAME_STATE::GAME_NEW;
};

#endif
