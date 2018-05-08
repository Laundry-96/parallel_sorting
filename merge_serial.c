#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int a[],int left,int endleft,int startright,int right);
void mergesort(int a[],int left,int right);
int number;
int main(){
  int *a, i, x;      
  FILE *file;
  file=fopen("listOfElements.txt", "r");
  fscanf(file,"%d",&number);
  a = (int *)malloc( number * sizeof(int));
  for(i = 0; i < number; i++){
      fscanf(file, "%d", &x);
      a[i] = x;
    }

  clock_t begin = clock();
  mergesort(a, 0, number-1);
  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("Elapsed time to sort a list of %d elements using merge sort = %.10f\n", number, time_spent);
  return 0;
}
void mergesort(int a[],int left,int right){
  int middle;  
  if(left<right)
    {
      middle=(left+right)/2;
      mergesort(a,left,middle);        
      mergesort(a,middle+1,right);    
      merge(a,left,middle,middle+1,right);  
    }
}
void merge(int a[],int left,int endleft,int startright,int right){
  int i,j,k;
  i=left;   
  j=startright;   
  k=0;
  int *b = (int *)malloc( number * sizeof(int));
  while(i<=endleft && j<=right){
      if(a[i]<a[j])
	b[k++]=a[i++];
      else
	b[k++]=a[j++];
    }
  while(i<=endleft){   
    b[k++]=a[i++];
  }
  while(j<=right){    
    b[k++]=a[j++];
  }
  for(i=left,j=0;i<=right;i++,j++){
    a[i]=b[j];
  }
  free(b);
}
 
