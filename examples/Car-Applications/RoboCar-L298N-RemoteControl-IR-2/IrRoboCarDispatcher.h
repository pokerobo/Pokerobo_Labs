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
    uint8_t getSpeed();
  private:
    RoboCarHandler *_roboCarHandler = NULL;
    uint8_t _baseSpeed = 255 - 3*15;
    uint8_t _gearNumber = 0;
    bool _asteriskButtonState = 0;
    bool _sharpButtonState = 0;
    bool _reversed = false;
};

#endif
