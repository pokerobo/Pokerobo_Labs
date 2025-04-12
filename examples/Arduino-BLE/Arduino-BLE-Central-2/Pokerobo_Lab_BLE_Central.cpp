#include "Pokerobo_Lab_BLE_Central.h"

PokeroboBLECentral::PokeroboBLECentral(String charactId) {
  _charactId = charactId;
}

void PokeroboBLECentral::begin(String localName) {
  if (!BLE.begin()) {
    this->log_(BLE_CENTRAL_BEGIN_FAILED);
    while (1);
  }

  _localName = localName;

  BLE.scan();
  this->log_(BLE_CENTRAL_DEVICE_SCANNING);
}

void PokeroboBLECentral::check() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    this->log_(BLE_CENTRAL_DEVICE_FOUND, &peripheral);

    if (peripheral.localName() == this->_localName) {
      BLE.stopScan();

      if (peripheral.connect()) {
        this->log_(BLE_CENTRAL_CONNECTED, &peripheral);

        if (peripheral.discoverAttributes()) {
          BLECharacteristic counterChar = peripheral.characteristic(this->_charactId.c_str());

          if (counterChar) {
            this->log_(BLE_CENTRAL_RECEIVING_BEGIN, &peripheral);

            while (peripheral.connected()) {
              // if (counterChar.valueUpdated()) {
                this->receive(counterChar);
              // }
            }

            this->log_(BLE_CENTRAL_RECEIVING_END, &peripheral);
          }
        }

        this->log_(BLE_CENTRAL_DISCONNECTED, &peripheral);
      } else {
        this->log_(BLE_CENTRAL_CONNECTING_FAILED);
      }

      BLE.scan(); // Quét lại nếu ngắt kết nối
    }
  }
}

void PokeroboBLECentral::receive(BLECharacteristic &charact) {}

void PokeroboBLECentral::log_(ble_central_log_t type, BLEDevice *device) {}
