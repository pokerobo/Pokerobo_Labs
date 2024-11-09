#include <Arduino.h>

const int trigPin = A2;    // Trigger Pin
const int echoPin = A3;    // Echo Pin
long duration, cm, inches;

void setup() {
  Serial.begin (57600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  delay(100);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print("Obstacle detected: ");
  Serial.print(cm);
  Serial.print("cm, ~ ");
  Serial.print(inches);
  Serial.print("in");
  Serial.println();
}
