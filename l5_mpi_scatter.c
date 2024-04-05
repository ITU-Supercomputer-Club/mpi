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
  
   
   double b[2] = {0.0};
   double *a = NULL;
   
   if (rank == MASTER) {
      a = (double *)malloc(10*sizeof(double));
      for (int i = 0; i < 10; i++)
         a[i] = 5.0*i;
   }   
   
   MPI_Scatter(a, 2, MPI_DOUBLE, b, 2, MPI_DOUBLE, MASTER, COMM);
   
   if (rank == 2)
      print_array(b, 2);
   

   MPI_Finalize();
 
}	
