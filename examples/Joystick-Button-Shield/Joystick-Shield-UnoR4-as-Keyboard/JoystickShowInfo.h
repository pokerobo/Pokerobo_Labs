#ifndef __POKEROBO_LAB_JOYSTICK_SHOW_INFO_H__
#define __POKEROBO_LAB_JOYSTICK_SHOW_INFO_H__

#include "Pokerobo_Lab_Display_Handler.h"

class JoystickShowInfo: public ProgramSticker {
  public:
    JoystickShowInfo(GeometryDisplayHandler* pen, char *_title = "Key Flags"): ProgramSticker(_title) {
      _pen = pen;
    }
    int begin();
    int check(void* action, void* command=NULL);
    int close();
    void render(JoystickAction* action);
    void show(JoystickAction* action);
  protected:
    void showFlags(u8g2_uint_t x, u8g2_uint_t y, char* label, uint16_t flags);
    char* int2bin(unsigned int x);
  private:
    GeometryDisplayHandler* _pen = NULL;
    u8g2_uint_t _charHeight = 0;
    u8g2_uint_t _charWidth = 0;
    char _buffer[17];
    u8g2_uint_t _titleX = 0;
    u8g2_uint_t _titleY = 15;
    char* _title = "BUTTONs";
};

#endif
