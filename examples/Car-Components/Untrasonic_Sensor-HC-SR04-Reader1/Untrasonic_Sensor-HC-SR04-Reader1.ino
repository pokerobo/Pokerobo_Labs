#include <Pokerobo_Car.h>

const int trigPin = A2;    // Trigger Pin
const int echoPin = A3;    // Echo Pin

UntrasonicReaderInRawCode sonar(trigPin, echoPin);

void setup() {
  Serial.begin(57600);
  sonar.begin();
}

void loop() {
  delay(100);
  Serial.print("Obstacle detected: ");
  Serial.print(sonar.distance_cm());
  Serial.print("cm, ~ ");
  Serial.print(sonar.distance_in());
  Serial.print("in");
  Serial.println();
}
