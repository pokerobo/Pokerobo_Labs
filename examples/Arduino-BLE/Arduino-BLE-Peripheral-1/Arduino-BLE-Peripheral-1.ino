#include <ArduinoBLE.h>

BLEService counterService("180C"); // Tạo dịch vụ BLE tùy chọn
BLEIntCharacteristic counterChar("2A56", BLERead | BLENotify); // đặc tính gửi giá trị int

int32_t counter = 0x7FFF0000;

void setup() {
  Serial.begin(57600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("BLE khởi động thất bại!");
    while (1);
  }

  BLE.setLocalName("UNO-R4-BLE");
  BLE.setAdvertisedService(counterService);

  counterService.addCharacteristic(counterChar);
  BLE.addService(counterService);

  counterChar.writeValue(counter); // Gửi giá trị ban đầu

  BLE.advertise();
  Serial.println("BLE Peripheral đang phát sóng...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Đã kết nối với: ");
    Serial.println(central.address());

    while (central.connected()) {
      counter++;
      counterChar.writeValue(counter); // Gửi giá trị mới
      Serial.print("Đã gửi: ");
      Serial.println(counter);
      delay(40); // mỗi 1 giây
    }

    Serial.println("Ngắt kết nối!");
  }
}
