#include "Pokerobo_Lab_BLE_Peripheral.h"

class MyBLEPeripheral: public PokeroboBLEPeripheral {
  public:
    using PokeroboBLEPeripheral::PokeroboBLEPeripheral;
  protected:
    void sendData() {
      counter++;
      (*charact).writeValue(counter); // Gửi giá trị mới
      Serial.print("Đã gửi: ");
      Serial.println(counter);
      // delay(40); // mỗi 1 giây
    }
  private:
    int32_t counter = 0x7FFF0000;
};

class MyBLEGenerator: public PokeroboBLEGenerator {
  public:
    bool read(int32_t &value) {
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
