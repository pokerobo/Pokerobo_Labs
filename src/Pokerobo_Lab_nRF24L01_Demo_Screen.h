#ifndef __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
#define __POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__

#include <Pokerobo_RCB_master.h>
#include <U8g2lib.h>

class SimpleDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    SimpleDisplayHandler(char *title);
    void renderMessage(char *text);
  private:
    char *_title = NULL;
};

#endif//__POKEROBO_LAB_NRF24L01_DEMO_SCREEN_H__
