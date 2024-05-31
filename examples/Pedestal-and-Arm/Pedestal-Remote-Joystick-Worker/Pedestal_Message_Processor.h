#ifndef __PEDESTAL_MESSAGE_PROCESSOR_H__
#define __PEDESTAL_MESSAGE_PROCESSOR_H__

#include <Pokerobo_RCB.h>
#include <Pokerobo_Arm.h>

class PedestalMessageProcessor: public MessageProcessor {
  public:
    PedestalMessageProcessor(PedestalController* pedestalController);
    void begin();
    int process(MasterContext* context, JoystickAction* control, MessageInterface* command);
  private:
    PedestalController* _pedestalController;
};

#endif
