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
  rf24.openReadingPipe(0, address);
  rf24.startListening();
}

void renderMessage(char *text) {
  Serial.print("Received ["), Serial.print(text), Serial.print(']');
  Serial.println();
}

void loop() {
  if (rf24.available()) {
    char text[20] = {0};
    rf24.read(&text, sizeof(text));
    renderMessage(text);
    delay(100);
  }
}
