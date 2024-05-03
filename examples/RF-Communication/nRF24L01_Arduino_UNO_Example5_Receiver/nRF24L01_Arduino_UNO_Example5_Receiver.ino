#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;

CaroRF24Receiver messageReceiver;

CounterMessagePacket messagePacket;
CounterMessageSerializer messageSerializer;
CounterDisplayHandler displayHandler("Receiver");

void setup() {
  Serial.begin(57600);

  messageReceiver.begin(address);

  displayHandler.begin();
}

void loop() {
  if (messageReceiver.available()) {
    char text[20] = {0};
    messageReceiver.read(text, sizeof(text));
    messageSerializer.decode(&messagePacket, text);
    displayHandler.renderMessage(&messagePacket);
    delay(100);
  }
}
