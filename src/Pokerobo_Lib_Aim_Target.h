#ifndef __POKEROBO_LIB_AIM_TARGET_H__
#define __POKEROBO_LIB_AIM_TARGET_H__

#include "Pokerobo_Lib_Display_Layout.h"

class AimTarget {
  public:
    AimTarget(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0, byte type=0xFF);
    void render();
    int8_t speedOfX(uint16_t x, uint16_t y);
    int8_t speedOfY(uint16_t x, uint16_t y);
    int8_t moveX(int8_t joyX);
    int8_t moveY(int8_t joyY);
  private:
    void drawPlus(int8_t x, int8_t y, int8_t d);
    byte _type;
    int8_t x;
    int8_t y;
    int8_t _maxX;
    int8_t _maxY;
    void* _u8g2Ref;
    lcd_layout_t _layout;
};

#endif
