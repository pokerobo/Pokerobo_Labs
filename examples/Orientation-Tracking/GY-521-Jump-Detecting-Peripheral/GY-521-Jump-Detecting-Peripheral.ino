#include <Wire.h>
#include <MPU6050.h>
#include "Pokerobo_Lab_BLE_Peripheral.h"

MPU6050 mpu;

int16_t ax, ay, az;  // Gia tốc trên các trục

class MyBLEGenerator: public PokeroboBLEGenerator {
  public:
    bool generate(int32_t &value) {
      mpu.getAcceleration(&ax, &ay, &az);
      value = ax;
      return true;
    }
};

MyBLEGenerator counter;
PokeroboBLEPeripheralDebugLogger serialLogger;
PokeroboBLEPeripheral counterPeripheral("2A56", "180C", &counter, &serialLogger);

void setup() {
  Wire.begin();
  Serial.begin(57600);

  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6500 is not connected!");
    while (1);
  }

  counterPeripheral.begin("JUMDINO-01", 20);
}

void loop() {
  counterPeripheral.check();
}
