#include "Pokerobo_Lab_BLE_Peripheral.h"

PokeroboBLEPeripheral::PokeroboBLEPeripheral(const char *charactId, const char* serviceId) {
  initialize(new BLEIntCharacteristic(charactId, BLERead | BLENotify), new BLEService(serviceId));
}

void PokeroboBLEPeripheral::initialize(BLEIntCharacteristic *charact_, BLEService *service_) {
  service = service_;
  charact = charact_;
}

void PokeroboBLEPeripheral::begin(const char* localName) {
  if (!BLE.begin()) {
    this->logBeginFailed_();
    while (1);
  }
  BLE.setLocalName(localName);
  BLE.setAdvertisedService(*service);
  (*service).addCharacteristic(*charact);
  BLE.addService(*service);
  BLE.advertise();
  this->logAdvertiseCalled_();
}

void PokeroboBLEPeripheral::check() {
  BLEDevice central = BLE.central();

  if (central) {
    logIsConnected_(central);
    while (central.connected()) {
      sendData();
    }
    logIsDisconnected_(central);
  }
}

void PokeroboBLEPeripheral::sendData() {}

void PokeroboBLEPeripheral::logBeginFailed_() {}
void PokeroboBLEPeripheral::logIsConnected_(BLEDevice& central) {}
void PokeroboBLEPeripheral::logIsDisconnected_(BLEDevice& central) {}
void PokeroboBLEPeripheral::logAdvertiseCalled_() {}
