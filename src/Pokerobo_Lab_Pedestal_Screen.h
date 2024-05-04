#ifndef __POKEROBO_LAB_PEDESTAL_SCREEN_H__
#define __POKEROBO_LAB_PEDESTAL_SCREEN_H__

#include <Pokerobo_RCB_master.h>

class PedestalDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    void render(JoystickAction *action);
  protected:
    virtual void renderInternal(JoystickAction *action);
};

#endif
