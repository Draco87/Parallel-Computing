# Parallel-Computing

This repository contains basic programs in C using the MPI library, designed to help understand the basics of Parallel and Distributed Computing. It covers topics like simple parallel computing programs, point-to-point communication, collective communication, blocking and non-blocking communication.

## Setup

### Initialization

First, you need to install MPI. If you are using a Unix-based system, you can usually install it via a package manager. For example, on Ubuntu, you can use:

```sh
sudo apt-get install mpich
```

### Compile the program

```sh
mpicc <filename>.c -o <filename>
```

### Run the program

```sh
mpirun -np <no. of processors> ./<filename>
```

## Program Order and Descriptions

Please refer to these programs in the following order for better understanding:

### Simple Programs to Understand the Concept

#### 1. sum.c
A simple program in C.

#### 2. mpi_sum.c
Parallelizes the `sum.c` program using the MPI library. Note that you can parallelize a simple C program using four MPI commands:
- `MPI_Init()`
- `MPI_Comm_rank()`
- `MPI_Comm_size()`
- `MPI_Finalize()`

#### 3. roots.c
Parallelizes the calculation of roots of a quadratic equation.

#### 4. mat_mult.c
Distributes the workload of matrix multiplication across multiple processes, allowing for faster computation of large matrices.

### Point-to-Point Communication Using Blocking & Non-Blocking Commands

#### 5. block.c
Each process sends its rank to the following process in a ring-like fashion.

#### 6. nblock.c
Each process calculates a different power of the received number 'x' (here, x = 10). For example, process 1 calculates \(10^1\), process 2 calculates \(10^2\), process 3 calculates \(10^3\), and so on.

### Collective Communication

#### 7. coll.c
This program initializes the number of elements (here, 12). The number of processors should be less than the number of elements. The program uses `MPI_Scatterv` to distribute distinct portions of data to different processors and then uses `MPI_Reduce` to sum them up on the root processor (0th processor).
