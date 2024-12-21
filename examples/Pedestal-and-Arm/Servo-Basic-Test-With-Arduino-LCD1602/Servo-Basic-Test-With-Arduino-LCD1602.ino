#include <Servo.h>
#include <Pokerobo_Car.h>

DisplayAdapter displayAdapter;

char positionStr[17] = {0};
char delayTimeStr[17] = {0};

void displayServoPosition(uint8_t position, int delayTime=1000) {
  sprintf(positionStr, "Servo: %3d", position);
  sprintf(delayTimeStr, "Delay: %d ms", delayTime);
  displayAdapter.render(1, 0, positionStr);
  displayAdapter.render(1, 1, delayTimeStr);
}

Servo servo;

void setup() {
  Serial.begin(57600);
  displayAdapter.begin();
  servo.attach(2);
  servo.write(0);
  delay(1000);
}
 
void loop() {
  servo.write(180);
  displayServoPosition(180, 1000);
  delay(1000);

  servo.write(90);
  displayServoPosition(90, 5000);
  delay(5000);

  servo.write(0);
  displayServoPosition(0, 5000);
  delay(5000);
}
