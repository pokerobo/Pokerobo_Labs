#ifndef __POKEROBO_LAB_BLE_PERIPHERAL_H__
#define __POKEROBO_LAB_BLE_PERIPHERAL_H__

#include <ArduinoBLE.h>

#define BLE_PERIPHERAL_BEGIN_FAILED  0x2001
#define BLE_PERIPHERAL_CONNECTED     0x2002
#define BLE_PERIPHERAL_DISCONNECTED  0x2003
#define BLE_PERIPHERAL_ADVERTISED    0x2004

class PokeroboBLELogger {
  public:
    virtual void log(uint16_t type, BLEDevice *device = NULL) {}
};

class PokeroboBLELoggerDebug: public PokeroboBLELogger {
  public:
    void log(uint16_t type, BLEDevice *device = NULL) {
      switch (type) {
      case BLE_PERIPHERAL_BEGIN_FAILED:
        Serial.println("BLE khởi động thất bại!");
        break;
      case BLE_PERIPHERAL_CONNECTED:
        if (device != NULL) {
          Serial.print("Đã kết nối với: ");
          Serial.println(device->address());
        } else {
          Serial.print("Đã kết nối!");
        }
        break;
      case BLE_PERIPHERAL_DISCONNECTED:
        Serial.println("Ngắt kết nối!");
        break;
      case BLE_PERIPHERAL_ADVERTISED:
        Serial.println("BLE Peripheral đang phát sóng...");
        break;
      }
    }
};

class PokeroboBLEPeripheral {
  public:
    PokeroboBLEPeripheral(const char *charactId, const char* serviceId,
        PokeroboBLELogger *logger = NULL);
    void begin(const char* localName);
    void check();
  protected:
    void initialize(BLEIntCharacteristic *charact, BLEService *service);
    virtual void sendData();
    BLEService *service = NULL;
    BLEIntCharacteristic *charact = NULL;
  private:
    PokeroboBLELogger *_logger = NULL;
};

#endif
