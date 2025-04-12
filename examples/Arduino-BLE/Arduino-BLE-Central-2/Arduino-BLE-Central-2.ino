#include "Pokerobo_Lab_BLE_Central.h"

class MyBLECentral: public PokeroboBLECentralWithLog {
  public:
    using PokeroboBLECentralWithLog::PokeroboBLECentralWithLog;
  protected:
    void receive(BLECharacteristic &charact) {
      int32_t value;
      charact.readValue(value);
      Serial.print("Nhận: ");
      Serial.println(value);
    }
};

MyBLECentral myBLECentral("2A56");

void setup() {
  Serial.begin(57600);
  myBLECentral.begin("UNO-R4-BLE");
}

void loop() {
  myBLECentral.check();
}
