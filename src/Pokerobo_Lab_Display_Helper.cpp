#include "Pokerobo_Lab_Display_Helper.h"

lcd_layout_t convertRotationToLayout(u8g2_cb_t *rotation) {
  if (rotation == U8G2_R0) return LCD_LAYOUT_R0;
  if (rotation == U8G2_R1) return LCD_LAYOUT_R1;
  if (rotation == U8G2_R2) return LCD_LAYOUT_R2;
  if (rotation == U8G2_R3) return LCD_LAYOUT_R3;
  return LCD_LAYOUT_R0;
}
