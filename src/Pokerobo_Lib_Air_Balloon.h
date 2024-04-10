#ifndef __POKEROBO_LIB_AIR_BALLOON_H__
#define __POKEROBO_LIB_AIR_BALLOON_H__

#include "Pokerobo_Lib_Display_Layout.h"

#define AIR_BALLOON_MIN_RADIUS  5
#define AIR_BALLOON_MAX_RADIUS  10

#ifndef AIR_BALLOONS_TOTAL
#define AIR_BALLOONS_TOTAL  20
#endif//AIR_BALLOONS_TOTAL

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
    bool isDisappeared();
    boolean isHit(int8_t aimX, int8_t aimY);
    void explode();
  private:
    balloon_state_t _state = BALLOON_STATE::NEW;
    int16_t _x;
    int16_t _y;
    int8_t _radius;
    int8_t _delay;
};

class PlaySpace {
  public:
    PlaySpace(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0, uint8_t total=AIR_BALLOONS_TOTAL);
    void begin();
    void change();
    void render();
    int8_t shoot(int8_t x, int8_t y);
  protected:
    void initBalloon(Balloon* balloon);
  private:
    uint16_t _arisingCount = 0;
    uint16_t _destroyCount = 0;
    uint16_t _missingCount = 0;
    uint8_t _total = 0;
    Balloon _balloons[AIR_BALLOONS_TOTAL];
    void* _u8g2Ref;
    lcd_layout_t _layout;
    int8_t _maxX;
    int8_t _maxY;
    uint8_t _maxCharHeight = 8;
    uint8_t _maxCharWidth = 5;
};

#endif