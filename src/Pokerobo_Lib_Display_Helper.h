#ifndef __POKEROBO_LIB_DISPLAY_HELPER_H__
#define __POKEROBO_LIB_DISPLAY_HELPER_H__

#include <U8g2lib.h>
#include <Arduino.h>
#include "Pokerobo_Lib_Display_Layout.h"

lcd_layout_t convertRotationToLayout(u8g2_cb_t *rotation);

#endif
