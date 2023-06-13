#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

  //These are not shared variables!
  //MPI does not allow shared variables
  int rank, size;

  // initialize MPI
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if(rank%2 == 0) {
    printf("This is rank %d, which is an even rank number \n", rank);
  }
  
  // finalize MPI
  MPI_Finalize();

}
