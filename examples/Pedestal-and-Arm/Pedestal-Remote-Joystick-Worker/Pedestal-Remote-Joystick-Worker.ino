#include <Pokerobo_RCB.h>
#include "Pedestal_Controller.h"
#include "Pedestal_Display_Handler.h"
#include "Pedestal_Message_Processor.h"

const uint64_t address = 0x18580901LL;

PedestalHandler pedestalHandler0( 0,  1);
PedestalHandler pedestalHandler1( 4,  5);
PedestalHandler pedestalHandler2( 8,  9);
PedestalHandler pedestalHandler3(14, 15);

PedestalGroup pedestalGroup(&pedestalHandler0,
    &pedestalHandler1,
    &pedestalHandler2,
    &pedestalHandler3);

PedestalController pedestalController(&pedestalGroup);

PedestalMessageProcessor messageProcessor(&pedestalController);

JoystickMessageSerializer messageSerializer;

RF24Tranceiver actionExecutor;

void setup() {
  Serial.begin(57600);

  pedestalGroup.begin();
  pedestalController.begin();

  actionExecutor.set(&messageProcessor);
  actionExecutor.set(&messageSerializer);
  actionExecutor.begin(RF24_RX, address);
}

void loop() {
  actionExecutor.check();
  delay(1);
}
