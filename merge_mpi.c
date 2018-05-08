#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
void merge(int *a, int *b, int left, int middle, int right) {
  int h, i, j, k;
  h = left;
  i = left;
  j = middle + 1;
  while((h <= middle) && (j <= right)) {
    if(a[h] <= a[j]) {
      b[i] = a[h];
      h++;
    }
    else { 
      b[i] = a[j];
      j++;
    }
    i++;
  }
  if(middle < h) { 
    for(k = j; k <= right; k++) {
      b[i] = a[k];
      i++;
    }
  }
  else { 
    for(k = h; k <= middle; k++) {
      b[i] = a[k];
      i++;
    }
  }
  for(k = left; k <= right; k++) { 
    a[k] = b[k];
  }
}

void mergeSort(int *a, int *b, int left, int right) { 
  int middle;
  if(left < right) {
    middle = (left + right)/2;
    mergeSort(a, b, left, middle);
    mergeSort(a, b, (middle + 1), right);
    merge(a, b, left, middle, right);
  }
}

int main(int argc, char** argv) {
  
  int n, i, x, p, myId;
  double start, end;
  FILE *file;
  
  file=fopen("listOfElements.txt", "r");
  fscanf(file,"%d",&n);
  int *original_array = malloc(n * sizeof(int));
  for(i = 0; i < n; i++){
      fscanf(file, "%d", &x);
      original_array[i] = x;
    }
 
  srand(time(NULL));

  printf("\n");
  printf("\n");
  
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myId);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  start = MPI_Wtime();
  int size = n/p;
  
  int *sub_array = malloc(size * sizeof(int));
  MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
  int *tmp_array = malloc(size * sizeof(int));
  mergeSort(sub_array, tmp_array, 0, (size - 1));
  int *sorted = NULL;
  if(myId == 0) {
    sorted = malloc(n * sizeof(int));
  }
  MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
  if(myId == 0) {
    int *other_array = malloc(n * sizeof(int));
    mergeSort(sorted, other_array, 0, (n - 1));
    end = MPI_Wtime(); 
    printf("\n Sorted %d elements in: %.16f seconds\n", n, end-start);
    free(sorted);
    free(other_array);  
  }
  free(original_array);
  free(sub_array);
  free(tmp_array);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
