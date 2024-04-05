#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"
#include "string.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

#define PI acos(-1)

// #define N 100000

double f(double x) {
   return 4.0 / (1.0 + x * x);
}

int main ( int argc, char *argv[] )
{
    int data;
    int rank, size;

    MPI_Init( &argc, &argv );
    
    MPI_Comm_rank( COMM, &rank );
    MPI_Comm_size( COMM, &size );
  
    MPI_Status status;
  
    int N = atoi(argv[1]);
  
    double left_sum = 0.0, right_sum = 0.0, left_pi = 0.0, right_pi = 0.0, h = 1.0/N;
    
    int i, chunk = N / size;
    
    for (i = rank * chunk; i < (rank+1)*chunk; i++) {
    	left_sum += h * f(i*h);
    	right_sum += h * f((i+1)*h);
    }	
    	
    MPI_Reduce(&left_sum, &left_pi, 1, MPI_DOUBLE, MPI_SUM, MASTER, COMM);
    
    MPI_Reduce(&right_sum, &right_pi, 1, MPI_DOUBLE, MPI_SUM, MASTER, COMM);
    
    if (rank == MASTER) {
    	printf("Exact PI   = %.10lf\n", PI);
    	printf("Approx. PI (Left) = %.10lf\n", left_pi);
    	printf("Approx. PI (Right) = %.10lf\n", right_pi);
    }
  
    MPI_Finalize();
 }   
    
