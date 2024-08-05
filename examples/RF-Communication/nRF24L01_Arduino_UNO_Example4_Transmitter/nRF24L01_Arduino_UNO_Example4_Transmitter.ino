#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;

CaroMessageGenerator messageGenerator;
CaroDisplayHandler displayHandler("Transmitter");

CaroRF24Transmitter messageTransmitter;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  messageTransmitter.begin(address);
}

void loop() {
  const char text[20];

  messageGenerator.createMessage(text);
  messageTransmitter.write(text, sizeof(text));
  displayHandler.renderMessage(text);

  delay(1000);
}
