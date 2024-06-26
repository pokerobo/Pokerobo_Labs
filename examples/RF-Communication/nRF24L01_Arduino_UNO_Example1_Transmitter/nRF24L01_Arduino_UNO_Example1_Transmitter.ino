#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t address = 0x123456789ABCDEF0LL;
const uint8_t pin_ce = 9;
const uint8_t pin_csn = 10;

RF24 rf24(pin_ce, pin_csn);

void setup() {
  Serial.begin(57600);

  rf24.begin();
  rf24.openWritingPipe(address);
  rf24.stopListening();
}

void createMessage(char *text);
void renderMessage(char *text);

void loop() {
  const char text[20];
  createMessage(text);
  renderMessage(text);
  rf24.write(&text, sizeof(text));

  delay(1000);
}

int count = 0;

void createMessage(char *text) {
  count = count + 1;
  sprintf(text, "Count: %d", count);
}

void renderMessage(char *text) {
  Serial.print("Received ["), Serial.print(text), Serial.print(']');
  Serial.println();
}
