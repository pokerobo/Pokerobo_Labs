#include "Pokerobo_Lab_SortingRunner_Insertion_Sort.h"

void InsertionSortingRunner::sort() {
  for (int i = 1; i < _total; ++i) {
    byte key = _array[i];
    int j = i - 1;
    while (j >= 0 && _array[j] > key) {
        _array[j + 1] = _array[j];
        j = j - 1;
    }
    _array[j + 1] = key;

    render();
  }
}
