#include <Arduino.h>

const uint8_t LED_PIN = LED_BUILTIN;

int lightOnTime = 2000;
int lightOffTime = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(lightOnTime);
  digitalWrite(LED_PIN, LOW);
  delay(lightOffTime);
}
