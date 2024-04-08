#ifndef __POKEROBO_LIB_WATER_BUBBLE_H__
#define __POKEROBO_LIB_WATER_BUBBLE_H__

#include "Pokerobo_Lib_Display_Layout.h"

#ifndef WATER_BUBBLES_TOTAL
#define WATER_BUBBLES_TOTAL  10
#endif//WATER_BUBBLES_TOTAL

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
};

class PlaySpace {
  public:
    PlaySpace(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0, uint8_t total=WATER_BUBBLES_TOTAL);
    void begin();
    void change();
    void render();
    int8_t shoot(int8_t x, int8_t y);
  private:
    uint8_t _total = 0;
    Balloon _balloons[WATER_BUBBLES_TOTAL];
    void* _u8g2Ref;
    lcd_layout_t _layout;
    int8_t _maxX;
    int8_t _maxY;
};

#endif
