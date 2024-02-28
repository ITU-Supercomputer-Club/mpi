#include <stdio.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD // Communicator

/*
    The processes form a loop, and each process passes its own rank added to the previous total to the next process.
*/
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    int left = (rank - 1 + size) % size;
    int right = (rank + 1) % size;

    // printf("Current: %d, left of current: %d, right of current: %d\n", rank, left, right);

    MPI_Status status;

    int own_sum = rank;
    int received_sum = 0;

    if (rank != MASTER) {
        MPI_Recv(&received_sum, 1, MPI_INT, left, TAG, COMM, &status);
        own_sum += received_sum;
        MPI_Send(&own_sum, 1, MPI_INT, right, TAG, COMM);
    } else {
        MPI_Send(&own_sum, 1, MPI_INT, right, TAG, COMM);
        MPI_Recv(&received_sum, 1, MPI_INT, left, TAG, COMM, &status);
    }
    printf("Received sum: %d, Current sum: %d, my rank: %d, rank of left: %d, rank of right: %d\n", received_sum, own_sum, rank, left, right);
    if (rank == MASTER)
        printf("Total rank sum is: %d\n", received_sum);
    MPI_Finalize();

    return 0;
}
