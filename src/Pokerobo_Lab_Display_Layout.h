#ifndef __POKEROBO_LIB_DISPLAY_LAYOUT_H__
#define __POKEROBO_LIB_DISPLAY_LAYOUT_H__

#include <Arduino.h>

typedef enum {
  LCD_LAYOUT_R0 = 0,
  LCD_LAYOUT_R1,
  LCD_LAYOUT_R2,
  LCD_LAYOUT_R3
} lcd_layout_t;

class CoordinateAxes {
  public:
    CoordinateAxes(void* u8g2Ref, lcd_layout_t layout=LCD_LAYOUT_R0);
    virtual void setLcdLayout(lcd_layout_t layout);
    virtual lcd_layout_t getLcdLayout();
    virtual void* getU8g2Ref();
    virtual int8_t getMaxX();
    virtual int8_t getMaxY();
  private:
    void* _u8g2Ref;
    lcd_layout_t _layout;
    int8_t _maxX;
    int8_t _maxY;
};

#endif
