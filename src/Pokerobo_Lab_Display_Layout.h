#ifndef __POKEROBO_LAB_DISPLAY_LAYOUT_H__
#define __POKEROBO_LAB_DISPLAY_LAYOUT_H__

#include "Pokerobo_Lab_Display_Handler.h"

typedef enum {
  LCD_LAYOUT_R0 = 0,
  LCD_LAYOUT_R1,
  LCD_LAYOUT_R2,
  LCD_LAYOUT_R3
} lcd_layout_t;

lcd_layout_t extractLcdLayout(GeometryDisplayHandler* pencil);

class CoordinateAxes {
  public:
    CoordinateAxes(GeometryDisplayHandler* pencil);
    virtual GeometryDisplayHandler* getPencil();
    virtual lcd_layout_t getLcdLayout();
    virtual void* getU8g2Ref();
    virtual int8_t getMaxX();
    virtual int8_t getMaxY();
  private:
    GeometryDisplayHandler* _pencil = NULL;
};

#endif
