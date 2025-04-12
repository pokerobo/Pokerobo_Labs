#ifndef __POKEROBO_LAB_BLE_PERIPHERAL_H__
#define __POKEROBO_LAB_BLE_PERIPHERAL_H__

#include <ArduinoBLE.h>

class PokeroboBLEPeripheral {
  public:
    PokeroboBLEPeripheral(const char *charactId, const char* serviceId);
    void begin(const char* localName);
    void check();
  protected:
    void initialize(BLEIntCharacteristic *charact, BLEService *service);
    virtual void sendData();
    virtual void logBeginFailed_();
    virtual void logIsConnected_(BLEDevice& central);
    virtual void logIsDisconnected_(BLEDevice& central);
    virtual void logAdvertiseCalled_();
    BLEService *service = NULL;
    BLEIntCharacteristic *charact = NULL;
};

class PokeroboBLEPeripheralWithLog: public PokeroboBLEPeripheral {
  public:
    using PokeroboBLEPeripheral::PokeroboBLEPeripheral;
  protected:
    void logBeginFailed_() {
      Serial.println("BLE khởi động thất bại!");
    }
    void logIsConnected_(BLEDevice& central) {
      Serial.print("Đã kết nối với: ");
      Serial.println(central.address());
    }
    void logIsDisconnected_(BLEDevice& central) {
      Serial.println("Ngắt kết nối!");
    }
    void logAdvertiseCalled_() {
      Serial.println("BLE Peripheral đang phát sóng...");
    }
};

#endif
