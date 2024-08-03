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
void renderMessage(char *text, bool result);

void loop() {
  const char text[20];

  createMessage(text);
  bool result = rf24.write(&text, sizeof(text));
  renderMessage(text, result);

  delay(100);
}

int count = 0;

void createMessage(char *text) {
  count = count + 1;
  sprintf(text, "Count: %d", count);
}

void renderMessage(char *text, bool result) {
  Serial.print("Sending ["), Serial.print(text), Serial.print(']');
  Serial.print(" result: "), Serial.print(result);
  Serial.println();
}
