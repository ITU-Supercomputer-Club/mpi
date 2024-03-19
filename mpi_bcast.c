#include <stdio.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

void print_array(int *x, int N) {
   for (int j = 0; j < N; j++)
      printf("%d\t", x[j]);
   printf("\n");
}

int main(int argc, char *argv[]) {

   MPI_Init(&argc, &argv);
   
   int rank, size;
   
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   int a[3] = {0, 0, 0};
   
   if (rank == MASTER) {
      a[0] = 3;
      a[1] = 7;
      a[2] = 15;
   }   
   
   MPI_Bcast(a, 3, MPI_INT, MASTER, COMM);
   
   if (rank == 2)
      print_array(a, 3);
   

   MPI_Finalize();
 
}	
