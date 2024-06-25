# Parallel-Computing
This repository contains basic programs in C using MPI library that can be deployed to understand the basics of Parallel &amp; Distributed Computing.
It covers topics like simple parallel computing programs to understand the basics, point-to-point communication, collective communication, blocking and non-blocking communication.

# A word
Please refer to these programs in this order:
## 1. sum.c
A simple program in C.
## 2. mpi_sum.c
To see how sum.c is parallelized using the MPI library.
Note that you can parallelize a simple C program using six MPI commands:
  . MPI_Init()
  . MPI_Comm_rank()
  . MPI_Comm_size()
  . MPI_Finalize()
