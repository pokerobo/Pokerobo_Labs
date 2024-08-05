#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;

CaroRF24Receiver messageReceiver;

CaroDisplayHandler displayHandler("Receiver");

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  messageReceiver.begin(address);
}

void loop() {
  if (messageReceiver.available()) {
    char text[20] = {0};
    messageReceiver.read(text, sizeof(text));
    displayHandler.renderMessage(text);
    delay(100);
  }
}
