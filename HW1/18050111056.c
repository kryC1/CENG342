/*
 * Author: Koray ÇELİK
 * Date: 23-04-03, 12:09
 * Description: This is the HW3 of CENG342
 *
 * Copyright (c) 2023 Koray ÇELİK
 */

#include <hellomake.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int my_rank, num_procs;

  int size_large = atoi(argv[1]);
  int size_small = atoi(argv[2]);

  char * filename = argv[3];

  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  myMatrixVectorMul(size_large, size_small, my_rank, num_procs, filename);
  myMatrixVectorMul(size_small, size_large, my_rank, num_procs, filename);

  MPI_Finalize();

  return(0);
}
