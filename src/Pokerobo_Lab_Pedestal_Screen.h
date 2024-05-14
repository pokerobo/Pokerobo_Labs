#ifndef __POKEROBO_LAB_PEDESTAL_SCREEN_H__
#define __POKEROBO_LAB_PEDESTAL_SCREEN_H__

#include <Pokerobo_Arm.h>
#include <Pokerobo_RCB_master.h>

class PedestalDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    void render(JoystickAction *action, PedestalState *state);
  protected:
    virtual void renderInternal(JoystickAction *action, PedestalState *state);
  private:
    char _title[16] = "Pedestals";
    char _lines[4][16] = {{0}, {0}, {0}, {0}};
};

#endif
