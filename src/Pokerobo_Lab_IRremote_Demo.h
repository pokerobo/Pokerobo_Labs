#ifndef __POKEROBO_LAB_IRREMOTE_DEMO_H__
#define __POKEROBO_LAB_IRREMOTE_DEMO_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include <IRremote.hpp>

class IrReceiverDisplayHandler: public GeometryDisplayHandler {
  public:
    using GeometryDisplayHandler::GeometryDisplayHandler;
    void renderMessage(char *text);
  protected:
    IrReceiverDisplayHandler(const char *title): GeometryDisplayHandler() {
      _title = title;
    }
    virtual void renderFrame();
    virtual void renderTitle();
  private:
    char *_title = NULL;
    
};

class IrDetectorDisplayHandler: public IrReceiverDisplayHandler {
  public:
    IrDetectorDisplayHandler(): IrReceiverDisplayHandler("IR Detector") {};
    void renderMessage(IRData *irData);
  protected:
    using IrReceiverDisplayHandler::IrReceiverDisplayHandler;
    virtual void prepareIrData(IRData *irData);
    void renderIrData();
  private:
    char _lines[2][32] = { {0}, {0} };
};

class IrConverterDisplayHandler: public IrDetectorDisplayHandler {
  public:
    IrConverterDisplayHandler(): IrDetectorDisplayHandler("IR Converter") {};
    void renderConversion(IRData *irData,
        decode_type_t aProtocol, uint16_t aAddress, uint16_t aCommand);
  protected:
    virtual void prepareIrData(IRData *irData,
        decode_type_t aProtocol, uint16_t aAddress, uint16_t aCommand);
    void renderIrData();
  private:
    char _targets[2][32] = { {0}, {0} };
};

#endif
