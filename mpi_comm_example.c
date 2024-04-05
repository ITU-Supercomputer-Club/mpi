#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"
#include "string.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

int main ( int argc, char *argv[] )
{
    int data;
    int globalRank, rank1, rank2, rank3, size;

    MPI_Init( &argc, &argv );
    
    MPI_Comm_rank( COMM, &globalRank );
    MPI_Comm_size( COMM, &size );
       
    MPI_Group globalGroup, group1, group2, group3;
    MPI_Comm subComm1, subComm2, subComm3;
      
    MPI_Comm_group(COMM, &globalGroup);
    
    int ranks1[3] = {0, 1, 2}, ranks2[3] = {3, 4, 5}, ranks3[2] = {6, 7};

    MPI_Group_incl(globalGroup, 3, ranks1, &group1);
    MPI_Group_incl(globalGroup, 3, ranks2, &group2);
    MPI_Group_incl(globalGroup, 2, ranks3, &group3);
    
    MPI_Comm_create(COMM, group1, &subComm1);
    MPI_Comm_create(COMM, group2, &subComm2);
    MPI_Comm_create(COMM, group3, &subComm3);
    
    // MPI_Comm_rank(subComm1, &rank1);
    // MPI_Comm_rank(subComm2, &rank2);
    // MPI_Comm_rank(subComm3, &rank3);
  
    printf("My Global Rank is %d\n", globalRank);
  
    /*
    if (globalRank < 3)
    	printf("My Global Rank is %d and My Local Rank is %d\n", globalRank, rank1);
    else if (globalRank < 6)
    	printf("My Global Rank is %d and My Local Rank is %d\n", globalRank, rank2);
    else
  	printf("My Global Rank is %d and My Local Rank is %d\n", globalRank, rank3);
  
    */
    MPI_Finalize();
 }   
    
