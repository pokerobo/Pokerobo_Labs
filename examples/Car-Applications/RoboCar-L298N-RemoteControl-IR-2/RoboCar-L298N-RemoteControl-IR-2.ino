#include "IrCodeMappings.h"
#include "IrRoboCarDispatcher.h"

RoboCarHandler roboCarHandler;

IrRoboCarDispatcher eventDispatcher(&roboCarHandler);

IRCodeMapper irCodeMapper;
IRListener irListener(&irCodeMapper, &eventDispatcher);

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();

  irCodeMapper.addMapping(11u, mappingPanasonic, 17u);
  // irCodeMapper.addMapping(23u, mappingSony, 17u);
  irListener.begin(2);
}

void loop() {
  uint32_t begin = millis();
  irListener.loop();
  delay(max(100 - (millis() - begin), 0));
}
