#ifndef __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
#define __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__

#include <Pokerobo_RCB_master.h>
#include <U8g2lib.h>

class SimpleDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    SimpleDisplayHandler(char *title): DisplayHandler() {
      _title = title;
    }
    void renderMessage(char *text) {
      U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
      int8_t _charHeight = _u8g2->getMaxCharHeight();
      int8_t _charWidth = _u8g2->getMaxCharWidth();
      this->firstPage();
      do {
        _u8g2->drawFrame(1, _charHeight + 1, 128 - 2, 64 - _charHeight - 2);
        if (_title != NULL) {
          _u8g2->drawStr(64 - _charWidth * strlen(_title) / 2, _charHeight, _title);
        }
        _u8g2->drawStr(64 - _charWidth * strlen(text) / 2, 32 + _charHeight / 2, text);
      } while (this->nextPage());
    }
  private:
    char *_title = NULL;
};

#endif//__POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
