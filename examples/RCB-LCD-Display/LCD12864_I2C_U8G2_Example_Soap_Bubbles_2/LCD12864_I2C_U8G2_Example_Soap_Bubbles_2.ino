#include "Pokerobo_Lab_Air_Balloon.h"

GeometryDisplayHandler displayHandler;

PlaySpace playSpace(&displayHandler, 5, 20, PLAY_SPACE_OPTION_STATUS_BAR);

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  playSpace.begin();
}

void loop() {
  playSpace.change();

  displayHandler.firstPage();
  do {
    playSpace.draw();
  } while (displayHandler.nextPage());

  delay(50);
}
