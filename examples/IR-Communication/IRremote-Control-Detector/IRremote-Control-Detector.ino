#include "Pokerobo_Lab_IRremote_Demo.h"

IrReceiverDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  IrReceiver.begin(A3, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    IRData decodedIRData = IrReceiver.decodedIRData;

    displayHandler.renderMessage(&decodedIRData);

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    IrReceiver.resume();
  }
  delay(50);
}
