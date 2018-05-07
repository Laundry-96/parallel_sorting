#include <stdio.h>
#include "random_gen.h"

void bubble_sort(int *data, int size);

int main() {
  int size, *rand_nums, i;
  size = 100;
  rand_nums = gen_numbers(size);

  for(i = 0; i < size; i++)
    printf("%d ", rand_nums[i]);

  printf("\n");

  bubble_sort(rand_nums, size);

  for(i = 0; i < size; i++)
    printf("%d ", rand_nums[i]);

  printf("\n");

}

void bubble_sort(int *data, int size) {
  int i, j, temp;

  for(i = 0; i < size - 1; i++) {
    
    for(j = 0; j < size - 1 - i; j++) {

      if(data[j] > data[j+1]) {
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
      }
    }
  } 
}
