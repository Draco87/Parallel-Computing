#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) 
{
    int size, rank, i = 0, sum = 0, gsum = 0;

    MPI_Init(&argc, &argv); // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process

    sum = 0;
    for(i = rank * 10 + 1; i <= rank * 10 + 10; i++) {
        sum = sum + i; // Calculate the local sum for each process
    }

    // Reduce all local sums to the global sum at the root process
    MPI_Reduce(&sum, &gsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    printf("rank = %d sum %d   gsum = %d \n", rank, sum, gsum);

    MPI_Finalize(); // Finalize the MPI environment

    return 0;
}
