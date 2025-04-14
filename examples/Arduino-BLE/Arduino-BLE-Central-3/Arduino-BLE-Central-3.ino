#include "Pokerobo_Lab_BLE_Central.h"

class MyBLEReceiver: public PokeroboBLEReceiver {
  public:
    void onReceive(int32_t value) {
      Serial.print("onReceive(): ");
      Serial.println(value);
    }
};

MyBLEReceiver myBLEReceiver;
PokeroboBLECentralDebugLogger serialLogger;
PokeroboBLECentral myBLECentral("2A56", &myBLEReceiver, &serialLogger);

void setup() {
  Serial.begin(57600);
  myBLECentral.begin("UNO-R4-BLE");
}

void loop() {
  Serial.println(" - loop() begin");
  myBLECentral.check();
  Serial.println(" - loop() end!");
  delay(50);
}
