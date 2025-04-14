#include "Pokerobo_Lab_BLE_Peripheral.h"

PokeroboBLEPeripheral::PokeroboBLEPeripheral(const char *charactId, const char* serviceId,
    PokeroboBLEGenerator *generator,
    PokeroboBLELogger *logger) {
  initialize(new BLEIntCharacteristic(charactId, BLERead | BLENotify), new BLEService(serviceId));
  _generator = generator;
  _logger = (logger != NULL) ? logger : new PokeroboBLELogger();
}

void PokeroboBLEPeripheral::initialize(BLEIntCharacteristic *charact_, BLEService *service_) {
  service = service_;
  charact = charact_;
}

void PokeroboBLEPeripheral::begin(const char* localName) {
  if (!BLE.begin()) {
    _logger->log(BLE_PERIPHERAL_BEGIN_FAILED);
    while (1);
  }
  BLE.setLocalName(localName);
  BLE.setAdvertisedService(*service);
  (*service).addCharacteristic(*charact);
  BLE.addService(*service);
  BLE.advertise();
  _logger->log(BLE_PERIPHERAL_ADVERTISED);
}

void PokeroboBLEPeripheral::check() {
  BLEDevice central = BLE.central();

  if (central) {
    _logger->log(BLE_PERIPHERAL_CONNECTED, &central);
    while (central.connected()) {
      sendData();
    }
    _logger->log(BLE_PERIPHERAL_DISCONNECTED, &central);
  }
}

void PokeroboBLEPeripheral::sendData() {
  if (_generator == NULL) return;
  int32_t value = 0;
  if (_generator->generate(value)) {
    (*charact).writeValue(value);
    _logger->log(BLE_PERIPHERAL_DATA_SENT, NULL, value);
  }
}
