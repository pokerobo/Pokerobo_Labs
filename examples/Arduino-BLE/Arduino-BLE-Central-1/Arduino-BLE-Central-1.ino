#include <ArduinoBLE.h>

BLEDevice peripheral;
BLECharacteristic counterChar;

void setup() {
  Serial.begin(57600);
  while (!Serial);

  BLE.setAdvertisedService
  if (!BLE.begin()) {
    Serial.println("BLE khởi động thất bại!");
    while (1);
  }

  Serial.println("Đang quét thiết bị BLE...");

  BLE.scan();
}

void loop() {
  peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Tìm thấy thiết bị: ");
    Serial.println(peripheral.localName());

    if (peripheral.localName() == "UNO-R4-BLE") {
      BLE.stopScan();

      if (peripheral.connect()) {
        Serial.println("Đã kết nối!");

        if (peripheral.discoverAttributes()) {
          counterChar = peripheral.characteristic("2A56");

          if (counterChar) {
            Serial.println("Đang nhận dữ liệu...");

            while (peripheral.connected()) {
              // if (counterChar.valueUpdated()) {
                int32_t value;
                counterChar.readValue(value);
                Serial.print("Nhận: ");
                Serial.println(value);
              // }
            }

            Serial.println("Ngắt kết nối!");
          }
        }
      } else {
        Serial.println("Kết nối thất bại!");
      }

      BLE.scan(); // Quét lại nếu ngắt kết nối
    }
  }
}
