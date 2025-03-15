#include "Pokerobo_Lab_SortingRunner_Selection_Sort.h"

void SelectionSortingRunner::sort() {
  for(int i=0; i<_total - 1; i++) {
    int min_pos = i;
    for(int j=i; j<_total; j++) {
      if (_array[j] < _array[min_pos]) {
        min_pos = j;
      }
    }
    if (min_pos > i) {
      swap(&_array[i], &_array[min_pos]);
    }
    render();
  }
}
