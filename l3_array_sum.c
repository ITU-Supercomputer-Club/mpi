#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

int *init_array(int r, int N) {
   int *v = (int *)malloc(N * sizeof(int));
   
   for (int j = 0; j < N; j++)
      v[j] = (r+1) * 10 + j;
      
   return v;
}

int *sum_arrays(int *x, int *y, int N) {
   int *z = (int *)malloc(N * sizeof(int));
   for (int j = 0; j < N; j++)
      z[j] = x[j] + y[j];
      
   return z;
}

void print_array(int *x, int N) {
   for (int j = 0; j < N; j++)
      printf("%d\t", x[j]);
   printf("\n");
}

int main ( int argc, char *argv[] )
{
    int data;
    int rank, size;

    MPI_Init( &argc, &argv );
    
    MPI_Comm_rank( COMM, &rank );
    MPI_Comm_size( COMM, &size );
  
    MPI_Status status;

    int *dizi = init_array(rank, 8);

    if (rank != MASTER) {
       
       MPI_Send(dizi, 8, MPI_INT, MASTER, TAG, COMM);
       
    } else {
       
       int *sum_dizi = (int *)malloc(8 * sizeof(int));
       int *temp_array = (int *)malloc(8 * sizeof(int));
       
       for (int j = 1; j < size; j++) {
          MPI_Recv(temp_array, 8, MPI_INT, j, TAG, COMM, &status);
          sum_dizi = sum_arrays(sum_dizi, temp_array, 8);
       }
       
       sum_dizi = sum_arrays(sum_dizi, dizi, 8); 
       
       print_array(sum_dizi, 8);
    
    }   
    

    MPI_Finalize();
    
}
