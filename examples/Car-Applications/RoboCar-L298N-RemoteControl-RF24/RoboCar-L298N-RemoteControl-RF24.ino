#include "Pokerobo_Car.h"

DisplayAdapter displayAdapter;

const uint64_t address = 0x18580901LL;
RF24Listener rf24Listener(address);
HangingDetector hangingDetector;

RoboCarHandler roboCarHandler;
MovingResolver movingResolver;

RemoteControlCar remoteControlCar(" Remote Control Car");

ProgramManager programManager;

void setup() {
  Serial.begin(57600);

  displayAdapter.begin();

  roboCarHandler.set(&movingResolver);
  roboCarHandler.begin();

  remoteControlCar.set(&displayAdapter);
  remoteControlCar.set(&roboCarHandler);
  remoteControlCar.begin();

  hangingDetector.begin([] (void ()) {
    displayAdapter.clear();
    displayAdapter.render(0, 0, "Suspending...");
    roboCarHandler.stop();
  }, 10);

  rf24Listener.begin();

  programManager.set(&rf24Listener);
  programManager.set(&displayAdapter);
  programManager.set(&hangingDetector);
  programManager.add(&remoteControlCar);
  programManager.begin();
}

void loop() {
  uint32_t begin = millis();
  programManager.check();
  delay(max(100 - (millis() - begin), 0));
}
