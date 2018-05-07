CC ?= gcc
MPICC ?= mpicc
all: mpi omp serial

mpi:
	$(MPICC) -g -Wall -o mpi_bubble bubble_sort_mpi.c random_gen.c

omp:
	$(CC) -o omp_bubble -fopenmp bubble_sort_openmp.c random_gen.c

serial:
	$(CC) bubble_sort_serial.c random_gen.c
