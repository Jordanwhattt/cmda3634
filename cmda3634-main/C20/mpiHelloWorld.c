#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

  int rank, size;
  
  // initialize MPI
  MPI_Init(&argc, &argv);

  // find out the id of this process
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // find out how many MPI processes there are
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("Hello world from MPI process %d of %d!\n",
	 rank, size);

  // finalize MPI
  MPI_Finalize();

}
