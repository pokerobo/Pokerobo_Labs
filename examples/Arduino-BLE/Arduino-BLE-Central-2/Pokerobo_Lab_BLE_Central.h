#ifndef __POKEROBO_LAB_BLE_CENTRAL_H__
#define __POKEROBO_LAB_BLE_CENTRAL_H__

#include <ArduinoBLE.h>

typedef enum BLE_CENTRAL_LOG_EVENT {
  BLE_CENTRAL_BEGIN_FAILED = 0,
  BLE_CENTRAL_DEVICE_SCANNING,
  BLE_CENTRAL_DEVICE_FOUND,
  BLE_CENTRAL_CONNECTED,
  BLE_CENTRAL_DISCONNECTED,
  BLE_CENTRAL_CONNECTING_FAILED,
  BLE_CENTRAL_RECEIVING_BEGIN,
  BLE_CENTRAL_RECEIVING_END,
} ble_central_log_t;

class PokeroboBLECentral {
  public:
    PokeroboBLECentral(String charactId);
    void begin(String localName);
    void check();
  protected:
    virtual void receive(BLECharacteristic &charact);
    virtual void log_(ble_central_log_t type, BLEDevice *device = NULL);
  private:
    String _charactId;
    String _localName;
};

class PokeroboBLECentralWithLog: public PokeroboBLECentral {
  public:
    using PokeroboBLECentral::PokeroboBLECentral;
  protected:
    void log_(ble_central_log_t type, BLEDevice *device = NULL) {
      switch (type) {
        case BLE_CENTRAL_BEGIN_FAILED:
          Serial.println("BLE khởi động thất bại!");
          break;
        case BLE_CENTRAL_DEVICE_SCANNING:
          Serial.println("Đang quét thiết bị BLE...");
          break;
        case BLE_CENTRAL_DEVICE_FOUND:
          Serial.print("Tìm thấy thiết bị: ");
          Serial.println(device->localName());
          break;
        case BLE_CENTRAL_CONNECTED:
          Serial.println("Đã kết nối!");
          break;
        case BLE_CENTRAL_DISCONNECTED:
          Serial.println("Ngắt kết nối!");
          break;
        case BLE_CENTRAL_CONNECTING_FAILED:
          Serial.println("Kết nối thất bại!");
          break;
        case BLE_CENTRAL_RECEIVING_BEGIN:
          Serial.println("Nhận dữ liệu...");
          break;
        case BLE_CENTRAL_RECEIVING_END:
          Serial.println("Nhận dữ liệu kết thúc");
          break;
        default:
          Serial.println("Log chưa phân loại");
      }
    }
};

#endif
