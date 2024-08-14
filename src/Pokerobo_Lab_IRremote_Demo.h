#ifndef __POKEROBO_LAB_IRREMOTE_DEMO_H__
#define __POKEROBO_LAB_IRREMOTE_DEMO_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include <IRremote.hpp>

class IrReceiverDisplayHandler: public GeometryDisplayHandler {
  public:
    using GeometryDisplayHandler::GeometryDisplayHandler;
    IrReceiverDisplayHandler(): GeometryDisplayHandler() {
      _title = "IR Receiver";
    }
    void renderMessage(char *text);
    void renderMessage(IRData *irData);
  protected:
    virtual void renderFrame();
    virtual void renderTitle();
    virtual void prepareIrData(IRData *irData);
    virtual void renderIrData(IRData *irData);
  private:
    void renderMessageOrString(IRData *irData, char *text);
    char *_title = NULL;
    char _lines[2][32] = { {0}, {0} };
};

#endif
