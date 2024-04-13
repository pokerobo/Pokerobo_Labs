#ifndef __POKEROBO_LIB_AIR_BALLOON_H__
#define __POKEROBO_LIB_AIR_BALLOON_H__

#include "Pokerobo_Lib_Display_Layout.h"

#define AIR_BALLOON_MIN_RADIUS        5
#define AIR_BALLOON_MAX_RADIUS        10

#ifndef CONCURRENT_BALLOONS_TOTAL
#define CONCURRENT_BALLOONS_TOTAL     20
#endif//CONCURRENT_BALLOONS_TOTAL

#ifndef APPEARANCE_BALLOONS_TOTAL
#define APPEARANCE_BALLOONS_TOTAL     1000
#endif//APPEARANCE_BALLOONS_TOTAL

#define PLAY_SPACE_OPTION_STATUS_BAR  0b00000001

typedef enum BALLOON_STATE {
  NEW = 0,
  FLYING,
  EXPLODED,
  ESCAPED,
} balloon_state_t;

class Balloon {
  friend class PlaySpace;
  public:
    Balloon();
    int16_t getX();
    int16_t getY();
    int8_t getRadius();
    int8_t getSpeed();
    bool isEscaped();
    bool isHit(int8_t aimX, int8_t aimY);
  private:
    balloon_state_t _state = BALLOON_STATE::NEW;
    int16_t _x;
    int16_t _y;
    int8_t _radius;
    int8_t _delay;
};

class PlaySpace {
  public:
    PlaySpace(CoordinateAxes* axes,
        uint8_t concurrentTotal=CONCURRENT_BALLOONS_TOTAL,
        uint16_t appearanceTotal=APPEARANCE_BALLOONS_TOTAL,
        uint8_t options = 0);
    void begin();
    void change();
    void render();
    int8_t shoot(int8_t x, int8_t y);
    bool isFailed();
    bool isFinished();
    void reset();
  protected:
    void resetBalloon(Balloon* balloon);
  private:
    uint16_t _arisingCount = 0;
    uint16_t _destroyCount = 0;
    uint16_t _missingCount = 0;
    uint16_t _appearanceTotal = 0;
    uint8_t _concurrentTotal = 0;
    Balloon _balloons[CONCURRENT_BALLOONS_TOTAL];
    CoordinateAxes* _axes;
    uint8_t _maxCharHeight = 8;
    uint8_t _maxCharWidth = 5;
    uint8_t _options = 0;
};

#endif
