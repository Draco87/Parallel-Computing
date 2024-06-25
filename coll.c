#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// FARSANA_IMS20105
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define the total number of elements
    int total_elements = 12;

    // The root process (rank 0) defines the data to be scattered
    int *sendbuf = NULL;
    if (rank == 0) {
        sendbuf = (int *)malloc(total_elements * sizeof(int));
        for (int i = 0; i < total_elements; ++i) {
            sendbuf[i] = i + 1; // Initialize with some values
        }
    }

    // Check if the number of processes is valid
    if (size > total_elements) {
        if (rank == 0) {
            printf("Invalid number of processors.\n Hint: The number of processors should be less than or equal to the total number of elements.\n");
        }
        MPI_Finalize();
        return 1; // Exit the program with an error code
    }

    // Define counts and displacements for scatterv
    int *sendcounts = (int *)malloc(size * sizeof(int));
    int *displs = (int *)malloc(size * sizeof(int));

    // Calculate counts and displacements
    int elements_per_proc = total_elements / size;
    for (int i = 0; i < size; ++i) {
        sendcounts[i] = elements_per_proc;
        displs[i] = i * elements_per_proc;
    }

    // Scatter the data to all processes
    int *recvbuf = (int *)malloc(elements_per_proc * sizeof(int));
    MPI_Scatterv(sendbuf, sendcounts, displs, MPI_INT, recvbuf, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the elements received by each processor
    printf("Processor %d received: [", rank);
    for (int i = 0; i < elements_per_proc; ++i) {
        printf("%d", recvbuf[i]);
        if (i < elements_per_proc - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Sum up the values on each process
    int local_sum = 0;
    for (int i = 0; i < elements_per_proc; ++i) {
        local_sum += recvbuf[i];
    }

    // Reduce the sums to the root process
    int global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the results
    if (rank == 0) {
        printf("Total sum: %d\n", global_sum);
    }

    free(sendbuf);
    free(sendcounts);
    free(displs);
    free(recvbuf);

    MPI_Finalize();
    return 0;
}
