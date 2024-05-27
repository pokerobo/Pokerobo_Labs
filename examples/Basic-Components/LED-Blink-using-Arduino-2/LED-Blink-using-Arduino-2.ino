#include <Arduino.h>

int count = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (count < 3) {
    count = count + 1;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    return;
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
