#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

void print_array(double *x, int N) {
   for (int j = 0; j < N; j++)
      printf("%.2f\t", x[j]);
   printf("\n");
}

int main(int argc, char *argv[]) {

   MPI_Init(&argc, &argv);
   
   int rank, size;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
  
   double *a_local = (double *)malloc(3*sizeof(double));
   for (int i = 0; i < 3; i++)
   	a_local[i] = 10.0*rank + i;
     
   double *a_global = NULL;
   
   if (rank == MASTER)
      a_global = (double *)malloc(size * 3 * sizeof(double));  
   
   MPI_Gather(a_local, 3, MPI_DOUBLE, a_global, 3, MPI_DOUBLE, MASTER, COMM);
   
   if (rank == MASTER)
      print_array(a_global, 3*size);
   

   MPI_Finalize();
 
}	
