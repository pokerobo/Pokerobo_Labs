#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;
const uint8_t pin_ce = 9;
const uint8_t pin_csn = 10;

RF24 rf24(pin_ce, pin_csn);
SimpleDisplayHandler displayHandler("Transmitter");

void setup() {
  Serial.begin(57600);

  rf24.begin();
  rf24.openWritingPipe(address);
  rf24.stopListening();

  displayHandler.begin();
}

void createMessage(char *text);

void loop() {
  const char text[20];
  createMessage(text);
  displayHandler.renderMessage(text);
  rf24.write(&text, sizeof(text));

  delay(1000);
}

int count = 0;

void createMessage(char *text) {
  count = count + 1;
  sprintf(text, "Counter: %d", count);
}
