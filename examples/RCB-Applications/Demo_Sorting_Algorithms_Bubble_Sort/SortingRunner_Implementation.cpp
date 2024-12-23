#include "SortingRunner_Implementation.h"

void BubbleSortingRunner::sort() {
  bool found;
  for(int i=0; i<_total - 1; i++) {
    found = false;
    for(int j=0; j < _total - i - 1; j++) {
      if (_array[j] > _array[j + 1]) {
        swap(&_array[j], &_array[j + 1]);
        found = true;
      }
      _sample->render();
    }
    if (!found) break;
  }
}
