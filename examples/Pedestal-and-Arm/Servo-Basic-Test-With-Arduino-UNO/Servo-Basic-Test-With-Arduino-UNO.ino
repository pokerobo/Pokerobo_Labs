#include <Servo.h>

Servo servo;

void setup() {
    servo.attach(2);
    servo.write(0);
    delay(1000);
}
 
void loop() {
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(6000);
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(6000);
}
