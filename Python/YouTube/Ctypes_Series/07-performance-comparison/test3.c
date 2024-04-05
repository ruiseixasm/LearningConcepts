#include <stdio.h>

void swap_c(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
 
int partition_c(int array[], int low, int high) {
   
  int pivot = array[high];
  int i = (low - 1);
 
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap_c(&array[i], &array[j]);
    }
  }
 
  swap_c(&array[i + 1], &array[high]);
  return (i + 1);
}
 
void quick_sort_c(int array[], int low, int high) {
  if (low < high) {
 
    int pi = partition_c(array, low, high);
     
    quick_sort_c(array, low, pi - 1);
    quick_sort_c(array, pi + 1, high);
  }
}


// Generate the .so file with this command
// gcc test3.c -shared -o test3.so -fPIC
