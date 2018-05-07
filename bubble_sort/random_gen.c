#include "random_gen.h"

int* gen_numbers(int size) {
  int *num, i;
  srand(time(NULL));
  
  num = (int *) malloc(sizeof(int) * size);

  for(i = 0; i < size; i++) {
    num[i] = rand() % 100;
  }

  return num;
}
