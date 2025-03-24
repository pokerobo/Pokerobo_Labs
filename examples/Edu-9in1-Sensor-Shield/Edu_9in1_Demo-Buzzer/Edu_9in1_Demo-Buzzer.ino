#include <Arduino.h>

#define ROTATION_PIN  A0
#define BUZZER_PIN    5

void setup() {
  pinMode(ROTATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int rotationVal = analogRead(ROTATION_PIN);
  int frequency = map(rotationVal, 0, 1023, 0, 1000);

  tone(BUZZER_PIN, frequency);

  delay(100);
}
