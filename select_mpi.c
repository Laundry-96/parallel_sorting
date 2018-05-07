#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
  int myid, numprocs;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  
  int x, i ,j, temp , size, part;
  int *Unsorted, *Sorted, *AofP, *SubArray;
  double start, end;
  FILE *file;

  if(myid == 0){
    file=fopen("listOfElements.txt", "r");
    fscanf(file,"%d",&size);

    Unsorted= malloc(size*sizeof(int));
    Sorted = malloc(size*sizeof(int));
    for(i = 0; i < size; i++){
      fscanf(file, "%d", &x);
      Unsorted[i] = x;
    }
   
    part = size/numprocs; 
    start = MPI_Wtime();

    AofP = malloc(numprocs*sizeof(int));
    for(i=0;i<numprocs;i++)
      AofP[i]=i*part;
  }
  
  MPI_Bcast(&part,1,MPI_INT,0,MPI_COMM_WORLD);
  SubArray = malloc(part*sizeof(int));
  MPI_Scatter(&Unsorted[0],part,MPI_INT,&SubArray[0],part,MPI_INT,0,MPI_COMM_WORLD);
 
  for(i=0;i<part;i++){
    for(j=i+1;j<part;j++){
      if(SubArray[i]>SubArray[j]){
	temp=SubArray[i];
	SubArray[i]=SubArray[j];
	SubArray[j]=temp;
      }
    }
  }

 
  MPI_Gather(&SubArray[0],part,MPI_INT,&Unsorted[0],part,MPI_INT,0,MPI_COMM_WORLD);
  if(myid==0){
    int hold, done, check;
    for(i=0;i<size;i++){  
      hold=0;
      done=0;
      while(done!=1){     
	if(AofP[hold]<(hold+1)*part){  
	  check = AofP[hold];
	  for(j=hold+1;j<numprocs;j++){
	    if(Unsorted[check]>Unsorted[AofP[j]] && AofP[j] < (j+1)*part){
	      check = AofP[j];
	      hold=j;
	    }
	  }
	  done=1;
	}else{
	  hold++;
	}
      }
      Sorted[i]=Unsorted[check];
      AofP[hold]++;
    }
    
    end = MPI_Wtime(); 
    printf("\n Sorted %d elements in: %.16f seconds\n", size, end-start);
    for(i=0; i<size; i++) printf(" %d", Sorted[i]);
    printf("\n");
  }
  
  MPI_Finalize();
  return 0;
}
