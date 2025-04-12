#include "Pokerobo_Lab_BLE_Peripheral.h"

PokeroboBLEPeripheral::PokeroboBLEPeripheral(const char *charactId, const char* serviceId,
    PokeroboBLELogger *logger) {
  initialize(new BLEIntCharacteristic(charactId, BLERead | BLENotify), new BLEService(serviceId));
  _logger = (logger != NULL) ? logger : new PokeroboBLELogger();
}

void PokeroboBLEPeripheral::initialize(BLEIntCharacteristic *charact_, BLEService *service_) {
  service = service_;
  charact = charact_;
}

void PokeroboBLEPeripheral::begin(const char* localName) {
  if (!BLE.begin()) {
    this->_logger->log(BLE_PERIPHERAL_BEGIN_FAILED);
    while (1);
  }
  BLE.setLocalName(localName);
  BLE.setAdvertisedService(*service);
  (*service).addCharacteristic(*charact);
  BLE.addService(*service);
  BLE.advertise();
  this->_logger->log(BLE_PERIPHERAL_ADVERTISED);
}

void PokeroboBLEPeripheral::check() {
  BLEDevice central = BLE.central();

  if (central) {
    this->_logger->log(BLE_PERIPHERAL_CONNECTED, &central);
    while (central.connected()) {
      sendData();
    }
    this->_logger->log(BLE_PERIPHERAL_DISCONNECTED, &central);
  }
}

void PokeroboBLEPeripheral::sendData() {}
