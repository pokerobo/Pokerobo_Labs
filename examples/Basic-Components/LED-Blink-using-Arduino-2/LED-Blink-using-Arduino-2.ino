#include <Arduino.h>

const uint8_t LED_PIN = LED_BUILTIN;

int lightOnTime = 2000;
int lightOffTime = 1000;
int count = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (count < 3) {
    count = count + 1;
    digitalWrite(LED_PIN, HIGH);
    delay(lightOnTime);
  }
  digitalWrite(LED_PIN, LOW);           
  delay(lightOffTime);
}
