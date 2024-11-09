#include <Arduino.h>
#include <NewPing.h>

const int trigPin = A2;    // Trigger Pin
const int echoPin = A3;    // Echo Pin

NewPing sonar(trigPin, echoPin);

void setup() {
  Serial.begin(57600);
}

void loop() {
  delay(100);
  Serial.print("Obstacle detected: ");
  Serial.print(sonar.ping_cm());
  Serial.print("cm, ~ ");
  Serial.print(sonar.ping_in());
  Serial.print("in");
  Serial.println();
}
