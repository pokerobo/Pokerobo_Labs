#include "SortingRunner_Implementation.h"

GeometryDisplayHandler pen;
SampleManager sample(&pen);
SelectionSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}