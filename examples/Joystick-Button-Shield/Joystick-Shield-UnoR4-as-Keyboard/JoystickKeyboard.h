#ifndef __POKEROBO_LAB_JOYSTICK_KEYBOARD_H__
#define __POKEROBO_LAB_JOYSTICK_KEYBOARD_H__

#include "Pokerobo_Lab_Display_Handler.h"

class ArduinoUnoR4AsKeyboard: public ProgramSticker {
  public:
    ArduinoUnoR4AsKeyboard(char *title = "Arrow Keys"): ProgramSticker(title) {}
    int begin();
    int check(void* action, void* command=NULL);
    int close();
};

#endif
