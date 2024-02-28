#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // The process retrieves its rank from the operating system.
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //The source code is read by all processes.

    if (!(rank % 2)) //Only even indices
        printf("Hello HPC! from process %d out of %d\n", rank, size);
    
    MPI_Finalize();
    
    printf("Final\n");
    return 0;
}
