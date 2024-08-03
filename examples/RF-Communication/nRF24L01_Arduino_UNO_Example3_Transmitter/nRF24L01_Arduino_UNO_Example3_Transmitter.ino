#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;

CaroDisplayHandler displayHandler("Transmitter");

CaroRF24Transmitter messageTransmitter;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  messageTransmitter.begin(address);
}

void createMessage(char *text);

void loop() {
  const char text[20];

  createMessage(text);
  displayHandler.renderMessage(text);
  messageTransmitter.begin(address);

  delay(1000);
}

int count = 0;

void createMessage(char *text) {
  count = count + 1;
  sprintf(text, "Counter: %d", count);
}
