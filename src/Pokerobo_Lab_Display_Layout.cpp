#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Layout.h"

CoordinateAxes::CoordinateAxes(GeometryDisplayHandler* pencil) {
  _pencil = pencil;
}

GeometryDisplayHandler* CoordinateAxes::getPencil() {
  return _pencil;
}

lcd_layout_t CoordinateAxes::getLcdLayout() {
  if (_pencil != NULL) {
    lcd_layout_t layout;
    DisplayOptions* options = _pencil->getOptions();
    if (options != NULL) {
      switch(options->getLcdRotation()) {
        case LCD_PINS_ON_TOP:
          layout = LCD_LAYOUT_R0;
          break;
        case LCD_PINS_ON_BOTTOM:
          layout = LCD_LAYOUT_R2;
          break;
        case LCD_PINS_ON_RIGHT:
          layout = LCD_LAYOUT_R1;
          break;
        case LCD_PINS_ON_LEFT:
          layout = LCD_LAYOUT_R3;
          break;
      }
    }
    return layout;
  }
  return LCD_LAYOUT_R2;
}

void* CoordinateAxes::getU8g2Ref() {
  return (_pencil != NULL) ? _pencil->getU8g2Ref() : NULL;
}

int8_t CoordinateAxes::getMaxX() {
  return (_pencil != NULL) ? _pencil->getDisplayWidth() - 1 : 0;
}

int8_t CoordinateAxes::getMaxY() {
  return (_pencil != NULL) ? _pencil->getDisplayHeight() - 1 : 0;
}
