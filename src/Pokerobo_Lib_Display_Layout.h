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
    CoordinateAxes(void* u8g2Ref, lcd_layout_t layout);
    void render();
};

#endif
