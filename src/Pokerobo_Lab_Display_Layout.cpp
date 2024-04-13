#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Layout.h"

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
  return _layout;
}

void* CoordinateAxes::getU8g2Ref() {
  return _u8g2Ref;
}

int8_t CoordinateAxes::getMaxX() {
  return _maxX;
}

int8_t CoordinateAxes::getMaxY() {
  return _maxY;
}
