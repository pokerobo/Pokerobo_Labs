#include "Pokerobo_Lab_SortingRunner_Heap_Sort.h"

GeometryDisplayHandler pen;
SampleManager sample(&pen);
HeapSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}
