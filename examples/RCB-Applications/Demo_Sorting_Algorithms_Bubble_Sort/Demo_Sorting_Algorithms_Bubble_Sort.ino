#include "Pokerobo_Lab_SortingRunner_Bubble_Sort.h"

GeometryDisplayHandler pen;
SampleManager sample(&pen);
BubbleSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}
