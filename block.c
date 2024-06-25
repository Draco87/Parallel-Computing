#include <stdio.h>
#include <mpi.h>

// FARSANA_IMS20105
int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int messageTag = 0;

    // Define the next and previous ranks in the ring
    int nextRank = (rank + 1) % size;
    int prevRank = (rank - 1 + size) % size;

    // Send the rank to the next process
    MPI_Send(&rank, 1, MPI_INT, nextRank, messageTag, MPI_COMM_WORLD);

    // Receive the rank from the previous process
    int receivedRank;
    MPI_Recv(&receivedRank, 1, MPI_INT, prevRank, messageTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Print the information
    printf("Process %d received rank %d from process %d\n", rank, receivedRank, prevRank);

    MPI_Finalize();
    return 0;
}
