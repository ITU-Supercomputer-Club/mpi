#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"
#include "string.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

struct complex{
   double a;
   double b;
};

struct complex complexAdd(struct complex z1, struct complex z2) {
   
   struct complex z3;
   z3.a = z1.a + z2.a;
   z3.b = z1.b + z2.b;
   
   return z3;
}


int main ( int argc, char *argv[] )
{
    int data;
    int rank, size;

    MPI_Init( &argc, &argv );
    
    MPI_Comm_rank( COMM, &rank );
    MPI_Comm_size( COMM, &size );
  
    int N = atoi( argv[1] );
    
    int i, chunk = N / size;
    
    double x, y;
    
    srand(time(NULL));
    
    struct complex z, zSumLocal, globalSum;
    
    for (i = 0; i < chunk; i++) {
    	z.a = 5.0 * (double)rand() / (double)RAND_MAX;
    	z.b = 5.0 * (double)rand() / (double)RAND_MAX;
    
        zSumLocal = complexAdd(zSumLocal, z);
    } 
    
    MPI_Op *MPI_COMPLEX_SUM;
    MPI_Op_create(complexAdd, 1, MPI_COMPLEX_SUM);
        
    MPI_Reduce(&zSumLocal, &globalSum, 1, MPI_INT, MPI_COMPLEX_SUM, MASTER, COMM);
    
    if (rank == MASTER) {
    	printf("okay!\n");
    	
    }
  
    MPI_Finalize();
 }   
    
