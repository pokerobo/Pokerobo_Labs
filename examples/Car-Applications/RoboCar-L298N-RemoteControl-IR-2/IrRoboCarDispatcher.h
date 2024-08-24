#ifndef __POKEROBO_CAR_IR_ROBOCAR_DISPATCHER_H__
#define __POKEROBO_CAR_IR_ROBOCAR_DISPATCHER_H__

#include "Pokerobo_Car.h"
#include "Pokerobo_IRx.h"

class IrRoboCarDispatcher: public IREventDispatcher {
  public:
    using IREventDispatcher::IREventDispatcher;
    IrRoboCarDispatcher(RoboCarHandler *roboCarHandler);
    void processOkButtonPressedEvent();
    void processDPadUpButtonPressedEvent();
    void processDPadRightButtonPressedEvent();
    void processDPadDownButtonPressedEvent();
    void processDPadLeftButtonPressedEvent();
    void processAsteriskButtonPressedEvent();
    void processSharpButtonPressedEvent();
    void processDigitButtonsPressedEvent(uint32_t buttons);
  protected:
    int getSpeed();
  private:
    RoboCarHandler *_roboCarHandler = NULL;
    uint8_t _baseSpeed = 255 - 3*10;
    uint8_t _gearNumber = 3;
    bool _asteriskButtonState = false;
    bool _sharpButtonState = false;
    bool _reversed = false;
};

#endif
