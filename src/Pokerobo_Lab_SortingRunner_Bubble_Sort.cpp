#include "Pokerobo_Lab_SortingRunner_Bubble_Sort.h"

void BubbleSortingRunner::sort() {
  bool found;
  for(int i=0; i<_total - 1; i++) {
    found = false;
    for(int j=0; j < _total - i - 1; j++) {
      if (_array[j] > _array[j + 1]) {
        swap(&_array[j], &_array[j + 1]);
        found = true;
      }
      if (_showStep) render();
    }
    if (!_showStep) render();
    if (!found) break;
  }
}
