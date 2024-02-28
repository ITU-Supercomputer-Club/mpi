#include <stdio.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD // Communicator

/*
    The summation of numbers from 1 to 100 using 4 processes.
*/
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    MPI_Status status; // It retains the outcome of a communication process and relevant information.
    // MPI_Request request; // For priority purposes 

    int i, local_sum = 0;

    for (i = 25 * rank + 1; i <= 25 * (rank + 1); i++) {
        local_sum += i;
    }

    printf("I am process %d, my local_sum is: %d\n", rank, local_sum);

    if (rank != MASTER) {
        MPI_Send(&local_sum, 1, MPI_INT, MASTER, TAG, COMM);
    } else {
        int chunk_sum = 0;
        for (int src = 1; src <= 3; src++) {
            MPI_Recv(&chunk_sum, 1, MPI_INT, src, TAG, COMM, &status);

            local_sum += chunk_sum;
        }

        printf("MASTER's local sum is: %d\n", local_sum);
        
    }

    MPI_Finalize();

    return 0;
}