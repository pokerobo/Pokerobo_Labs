#include "Pokerobo_Lab_BLE_Peripheral.h"

class MyBLEGenerator: public PokeroboBLEGenerator {
  public:
    bool generate(int32_t &value) {
      value = counter++;
      return true;
    }
  private:
    int32_t counter = 0x7FFF0000;
};

MyBLEGenerator counter;
PokeroboBLEPeripheralDebugLogger serialLogger;
PokeroboBLEPeripheral counterPeripheral("2A56", "180C", &counter, &serialLogger);

void setup() {
  Serial.begin(57600);
  counterPeripheral.begin("UNO-R4-BLE");
}

void loop() {
  counterPeripheral.check();
}
