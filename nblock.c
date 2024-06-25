#include <stdio.h>
#include <mpi.h>

// FARSANA_IMS20105
int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double recv_time;

    int x = 10;
    if (rank == 0) {
        // Process 0 initializes the value of x

        // Process 0 initiates non-blocking send
        MPI_Request send_request;
        MPI_Isend(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &send_request);

        MPI_Wait(&send_request, MPI_STATUS_IGNORE);

        // printf("Process %d: Sent x asynchronously.\n", rank);
    } else {
        // Other processes receive the value of x asynchronously
        MPI_Request recv_request;
        MPI_Irecv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &recv_request);

        // Capture the timestamp when receiving x
        recv_time = MPI_Wtime();

        // Continue with calculations using x
        int result = 1;
        for (int i = 0; i < rank; ++i) {
            result *= x;
        }
        printf("Process %d calculated result: %d\n", rank, result);

        // printf("\n");

        // printf("Process %d: Received x asynchronously at timestamp: %f seconds\n", rank, recv_time);
    }

    MPI_Finalize();
    return 0;
}
