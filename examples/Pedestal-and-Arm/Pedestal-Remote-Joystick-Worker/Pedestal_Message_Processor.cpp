#include "Pedestal_Message_Processor.h"

PedestalMessageProcessor::PedestalMessageProcessor(PedestalController* pedestalController) {
  _pedestalController = pedestalController;
}

int PedestalMessageProcessor::process(MasterContext* context, JoystickAction* action, MessageInterface* command) {
  _pedestalController->play(action->getPressingFlags(), action->getX(), action->getY());
  return 1;
}
