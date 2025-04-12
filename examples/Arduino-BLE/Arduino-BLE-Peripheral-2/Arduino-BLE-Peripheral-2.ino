#include "Pokerobo_Lab_BLE_Peripheral.h"

class MyBLEPeripheral: public PokeroboBLEPeripheralWithLog {
  public:
    using PokeroboBLEPeripheralWithLog::PokeroboBLEPeripheralWithLog;
  protected:
    void sendData();
  private:
    int32_t counter = 0x7FFF0000;
};

void MyBLEPeripheral::sendData() {
  counter++;
  (*charact).writeValue(counter); // Gửi giá trị mới
  Serial.print("Đã gửi: ");
  Serial.println(counter);
  // delay(40); // mỗi 1 giây
}

MyBLEPeripheral counterPeripheral("2A56", "180C");

void setup() {
  Serial.begin(57600);
  counterPeripheral.begin("UNO-R4-BLE");
}

void loop() {
  counterPeripheral.check();
}
