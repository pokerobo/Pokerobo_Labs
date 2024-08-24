#define DECODE_NEC
#define DECODE_PANASONIC
#define DECODE_SONY

#include "Pokerobo_Lab_IRremote_Demo.h"

IrInterceptorDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  IrSender.begin(A2, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  IrReceiver.begin(A3, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    IRData irData = IrReceiver.decodedIRData;
    size_t sent = IrSender.write(&irData, 2);

    displayHandler.renderMessage(&irData);

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    IrReceiver.resume();
  }
  delay(100);
}
