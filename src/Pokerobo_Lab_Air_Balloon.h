#ifndef __POKEROBO_LAB_AIR_BALLOON_H__
#define __POKEROBO_LAB_AIR_BALLOON_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include "Pokerobo_Lab_Display_Layout.h"

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
  BALLOON_NEW = 0,
  BALLOON_FLYING,
  BALLOON_EXPLODED,
  BALLOON_ESCAPED,
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
    balloon_state_t _state = BALLOON_STATE::BALLOON_NEW;
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
    PlaySpace(GeometryDisplayHandler* pencil,
        uint8_t concurrentTotal=CONCURRENT_BALLOONS_TOTAL,
        uint16_t appearanceTotal=APPEARANCE_BALLOONS_TOTAL,
        uint8_t options = 0);
    void begin();
    void change();
    void draw();
    int8_t shoot(int8_t x, int8_t y);
    bool isFinished();
    virtual bool hasLost();
    virtual void reset();
  protected:
    void initialize(uint8_t concurrentTotal, uint16_t appearanceTotal, uint8_t options);
    void resetBalloon(Balloon* balloon);
    virtual void onBalloonExploded(Balloon* balloon);
    virtual void onBalloonEscaped(Balloon* balloon);
    virtual void drawExplodingBalloon(Balloon* balloon);
    virtual void drawFlyingBalloon(Balloon* balloon);
    virtual void drawGameInfoBar();
    void prepareToDrawGameInfoBar();
    CoordinateAxes* getCoordinateAxes();
    GeometryDisplayHandler* getPencil();
    uint8_t getCharHeight();
    uint8_t getCharWidth();
    uint16_t getRemainingBalloonTotal();
    uint16_t getExplodedBalloonTotal();
    uint16_t getEscapedBalloonTotal();
  private:
    uint16_t _arisingCount = 0;
    uint16_t _destroyCount = 0;
    uint16_t _missingCount = 0;
    uint16_t _appearanceTotal = 0;
    uint8_t _concurrentTotal = 0;
    Balloon _balloons[CONCURRENT_BALLOONS_TOTAL];
    CoordinateAxes* _axes = NULL;
    GeometryDisplayHandler* _pencil = NULL;
    uint8_t _options = 0;
};

#endif
