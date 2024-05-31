#include "Pokerobo_Lab_Display_Layout.h"

CoordinateAxes::CoordinateAxes(GeometryDisplayHandler* pencil) {
  _pencil = pencil;
}

GeometryDisplayHandler* CoordinateAxes::getPencil() {
  return _pencil;
}

lcd_layout_t CoordinateAxes::getLcdLayout() {
  if (_pencil != NULL) {
    DisplayOptions* options = _pencil->getOptions();
    if (options != NULL) {
      switch(options->getLcdRotation()) {
        case LCD_PINS_ON_TOP:
          return LCD_LAYOUT_R0;
        case LCD_PINS_ON_BOTTOM:
          return LCD_LAYOUT_R2;
        case LCD_PINS_ON_RIGHT:
          return LCD_LAYOUT_R1;
        case LCD_PINS_ON_LEFT:
          return LCD_LAYOUT_R3;
      }
    }
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
