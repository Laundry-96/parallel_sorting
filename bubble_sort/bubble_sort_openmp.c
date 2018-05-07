#include <stdio.h>
#include "random_gen.h"
#include <omp.h>
void bubble_sort(int *data, int size);

int main() {
  int size, *rand_nums, i;
  size = 100000;
  rand_nums = gen_numbers(size);

  for(i = 0; i < size; i++)
    printf("%d ", rand_nums[i]);

  printf("\nAAAAAHH\n");

  bubble_sort(rand_nums, size);

  for(i = 0; i < size; i++)
    printf("%d ", rand_nums[i]);

  printf("\n");

}

void bubble_sort(int *data, int size) {
  int i, j, temp, first;

  for(i = 0; i < size - 1; i++) {
    first = i % 2;

    #pragma omp parallel for default(none), shared(data, first, size, i), private(temp)
    for(j = first; j < size - 1; j+=2) {
      if(data[j] > data[j+1]) {
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
      }
    }
  } 
}
