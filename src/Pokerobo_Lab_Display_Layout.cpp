#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Layout.h"

CoordinateAxes::CoordinateAxes(GeometryDisplayHandler* pencil) {
  _pencil = pencil;
}

CoordinateAxes::CoordinateAxes(void* u8g2Ref, lcd_layout_t layout) {
  _u8g2Ref = u8g2Ref;
  setLcdLayout(layout);
}

void CoordinateAxes::setLcdLayout(lcd_layout_t layout) {
  _layout = layout;
  _maxX = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 127 : 63;
  _maxY = (_layout == LCD_LAYOUT_R0 || _layout == LCD_LAYOUT_R2) ? 63 : 127;
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
  return _layout;
}

void* CoordinateAxes::getU8g2Ref() {
  if (_pencil != NULL) {
    return _pencil->getU8g2Ref();
  }
  return _u8g2Ref;
}

int8_t CoordinateAxes::getMaxX() {
  if (_pencil != NULL) {
    return _pencil->getDisplayWidth() - 1;
  }
  return _maxX;
}

int8_t CoordinateAxes::getMaxY() {
  if (_pencil != NULL) {
    return _pencil->getDisplayHeight() - 1;
  }
  return _maxY;
}
