#ifndef __POKEROBO_LIB_AIR_BALLOON_H__
#define __POKEROBO_LIB_AIR_BALLOON_H__

#include "Pokerobo_Lib_Display_Layout.h"

#define AIR_BALLOON_MIN_RADIUS  5
#define AIR_BALLOON_MAX_RADIUS  10

#ifndef AIR_BALLOONS_TOTAL
#define AIR_BALLOONS_TOTAL  20
#endif//AIR_BALLOONS_TOTAL

class Balloon {
  friend class PlaySpace;
  public:
    Balloon();
    int16_t getX();
    int16_t getY();
    int8_t getR();
    int8_t getSpeed();
    bool isDisappeared();
    boolean isHit(int8_t aimX, int8_t aimY);
    void explode();
  private:
    int8_t r;
    int16_t x;
    int16_t y;
    int8_t _delay;
};

class PlaySpace {
  public:
    PlaySpace(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0, uint8_t total=AIR_BALLOONS_TOTAL);
    void begin();
    void change();
    void render();
    int8_t shoot(int8_t x, int8_t y);
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
};

#endif
