#ifndef __POKEROBO_LIB_WATER_BUBBLE_H__
#define __POKEROBO_LIB_WATER_BUBBLE_H__

#include "Pokerobo_Lib_Display_Layout.h"

#ifndef WATER_BUBBLES_TOTAL
#define WATER_BUBBLES_TOTAL  10
#endif//WATER_BUBBLES_TOTAL

class Bubble {
  friend class Aquarium;
  public:
    Bubble();
    bool isDisappeared();
    int8_t getSpeed();
    boolean isHit(int8_t aimX, int8_t aimY);
    void explode();
  private:
    int8_t r;
    int16_t x;
    int16_t y;
};

class Aquarium {
  public:
    Aquarium(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0, uint8_t total=WATER_BUBBLES_TOTAL);
    void begin();
    void change();
    void render();
    int8_t shoot(int8_t x, int8_t y);
  private:
    uint8_t _total = 0;
    Bubble _bubbles[WATER_BUBBLES_TOTAL];
    void* _u8g2Ref;
    lcd_layout_t _layout;
    int8_t _maxX;
    int8_t _maxY;
};

#endif
