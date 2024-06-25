#include <stdio.h>
#include <mpi.h>
#include <math.h>

//FARSANA_IMS20105
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    double a = 2.0, b = -5.0, c = 2.0; // coefficients of the quadratic equation
    double discriminant, root1, root2;

    // Broadcast coefficients to all processes
    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&c, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Each process calculates its root
    discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        if (rank == 0) {
            root1 = (-b + sqrt(discriminant)) / (2 * a);
        } else {
            root2 = (-b - sqrt(discriminant)) / (2 * a);
        }
    }

    // Use separate buffers for sending and receiving in MPI_Gather
    double gatheredRoots[2];

    // Gather roots from all processes to process 0
    MPI_Gather(&root1, 1, MPI_DOUBLE, gatheredRoots, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&root2, 1, MPI_DOUBLE, gatheredRoots + 1, 1, MPI_DOUBLE, 1, MPI_COMM_WORLD);

    // Display the roots by process 0
    if (rank == 0) {
        printf("Root 1: %.2f\n", gatheredRoots[0]);
        printf("Root 2: %.2f\n", gatheredRoots[1]);
    }

    MPI_Finalize();
    return 0;
}
