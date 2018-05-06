// C program for selection sort
#include <stdio.h>
#include <math.h>
#include <time.h> 

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
 
void selectionSort(int arr[], int n)
{
  int i, j, min_idx;
 
  // One by one move boundary of unsorted subarray
  for (i = 0; i < n-1; i++)
    {
      // Find the minimum element in unsorted array
      min_idx = i;
      for (j = i+1; j < n; j++)
	if (arr[j] < arr[min_idx])
	  min_idx = j;
 
      // Swap the found minimum element with the first element
      swap(&arr[min_idx], &arr[i]);
    }
} 
// A utility function to print an array of size n
void printArray(int arr[], int n)
{
  int i;
  for (i=0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
 
 
 
/* Driver program to test insertion sort */
int main()
{

  FILE *file;
  int i;
  int size;
  int x = 0;

  file=fopen("listOfElements.txt", "r");
  fscanf(file,"%d",&size);

  int arr[size];
  for(i = 0; i < size; i++){
      fscanf(file, "%d", &x);
      arr[i] = x;
  }
  
  clock_t begin = clock(); 
  selectionSort(arr, size);
  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printArray(arr, size);
  printf("Elapsed time to sort a list of %d elements using bubble sort = %.10f\n", size, time_spent);
  
  return 0;
}
