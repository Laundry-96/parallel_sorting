#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include "random_gen.h"
void bubble_sort(int *data, int size);
int *merge(int *chunk1, int chunk1_size, int *chunk2, int chunk2_size);

int main(int argc, char **argv) {
  //Data is the data that we have
  //Chunk is a subset of data that is used per processer
  //
  //Data_size is how much data we have
  //Chunk_size is how much per chunk
  //Step is something
  int *data, *chunk, *other, data_size, chunk_size, step, other_size;
  int proc_id, num_procs;

  int source, tag;

  MPI_Status status;

  data_size = 100000;
  source = 0;
  tag = 123;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if(proc_id == 0) {

    data = gen_numbers(data_size);

    chunk_size = data_size/num_procs;

    MPI_Bcast(&chunk_size, 1, MPI_INT, source, MPI_COMM_WORLD);
    chunk = (int*) malloc(chunk_size * sizeof(int));
    MPI_Scatter(data, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, source, MPI_COMM_WORLD);

    bubble_sort(chunk, chunk_size);
  }

  else {
    MPI_Bcast(&chunk_size, 1, MPI_INT, source, MPI_COMM_WORLD);
    chunk = (int*) malloc(chunk_size * sizeof(int));
    MPI_Scatter(data, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, source, MPI_COMM_WORLD);

    bubble_sort(chunk, chunk_size);
  }

  step = 1;
  while(step < num_procs) {
    if(proc_id % (2*step) == 0) {
      if(proc_id + step < num_procs) {
        MPI_Recv(&other_size, 1, MPI_INT, proc_id + step, source, MPI_COMM_WORLD, &status);
        other = (int *) malloc(other_size*sizeof(int));
        MPI_Recv(other, other_size, MPI_INT, proc_id + step, source, MPI_COMM_WORLD, &status);
        chunk = merge(chunk, chunk_size, other, other_size);
        chunk_size += other_size;
      }
    }
    
    else {
      int near = proc_id - step;
      MPI_Send(&chunk_size, 1, MPI_INT, near, source, MPI_COMM_WORLD);
      MPI_Send(chunk, chunk_size, MPI_INT, near, source, MPI_COMM_WORLD);
      break;
    }

    step *= 2;
  }

  if(proc_id == 0) {
    int i;

    for (i = 0; i < chunk_size; i++) {
      printf("%d ", chunk[i]);
    }

    printf("\n");
  }

  MPI_Finalize();
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

int *merge(int *chunk1, int chunk1_size, int *chunk2, int chunk2_size) {
  int c1_p, c2_p, md_p;
  int *result;

  result = (int *) malloc(sizeof(int) * (chunk1_size + chunk2_size));

  c1_p = 0; c2_p = 0; md_p = 0;

  while(c1_p < chunk1_size && c2_p < chunk2_size) {
    if(chunk1[c1_p] < chunk2[c2_p]) {
      result[md_p] = chunk1[c1_p];
      c1_p++;
    }
    else {
      result[md_p] = chunk2[c2_p];
      c2_p++;
    }

    md_p++;
  }

  if(c1_p == chunk1_size) {
    while(c2_p != chunk2_size) {
      result[md_p] = chunk2[c2_p];
      c2_p++; md_p++;
    }
  }

  if(c2_p == chunk2_size) {
    while(c1_p != chunk1_size) {
      result[md_p] = chunk1[c1_p];
      c1_p++; md_p++;
    }
  }

  return result;
}
