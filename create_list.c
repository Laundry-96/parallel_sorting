#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int main(int argc, char **argv){
  int size = 100;
  FILE *listOfElements=fopen("listOfElements.txt", "w");
  int a; 
  // size of list
  fprintf(listOfElements, "%d\n", size);

  fprintf(listOfElements, "\n");

  srand(0);

  // populate list
  for(a=0;a<size;a++){            
      fprintf(listOfElements, "%d\t", rand() % size);
  }
   fprintf(listOfElements, "\n");
 
  fclose(listOfElements);

  return 0;
}//end main
