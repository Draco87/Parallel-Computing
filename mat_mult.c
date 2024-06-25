#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 4

// FARSANA_IMS20105
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrixA[MATRIX_SIZE][MATRIX_SIZE];
    int matrixB[MATRIX_SIZE][MATRIX_SIZE];
    int result[MATRIX_SIZE][MATRIX_SIZE];

    // Initialize matrices on the root process
    if (rank == 0) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrixA[i][j] = i + j;
                matrixB[i][j] = i - j;
            }
        }
    }

    // Broadcast matrices to all processes
    MPI_Bcast(matrixA, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(matrixB, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute portion of the result matrix
    int startRow = rank * MATRIX_SIZE / size;
    int endRow = (rank + 1) * MATRIX_SIZE / size;

    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // Gather results from all processes to the root process
    MPI_Gather(rank == 0 ? MPI_IN_PLACE : result + startRow, (endRow - startRow) * MATRIX_SIZE, MPI_INT,
               result, (endRow - startRow) * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the result on the root process
    if (rank == 0) {
        printf("Matrix A:\n");
        printMatrix(matrixA, MATRIX_SIZE);

        printf("Matrix B:\n");
        printMatrix(matrixB, MATRIX_SIZE);

        printf("Result Matrix:\n");
        printMatrix(result, MATRIX_SIZE);
    }

    MPI_Finalize();
    return 0;
}
