#include "Pokerobo_Lab_nRF24L01_Demo_Screen.h"

const uint64_t address = 0x123456789ABCDEF0LL;

JoystickHandler joystickHandler;

JoystickEventPacket messagePacket;
JoystickEventGenerator messageGenerator(&joystickHandler);
JoystickEventSerializer messageSerializer;
JoystickEventDisplayHandler displayHandler("Transmitter");

CaroRF24Transmitter messageTransmitter;

void setup() {
  Serial.begin(57600);

  messageTransmitter.begin(address);

  joystickHandler.begin();

  displayHandler.begin();
}

void loop() {
  const char text[20];
  messageGenerator.createMessage(&messagePacket);
  displayHandler.renderMessage(&messagePacket);
  messageSerializer.encode(text, &messagePacket);
  messageTransmitter.write(text, sizeof(text));

  delay(100);
}
