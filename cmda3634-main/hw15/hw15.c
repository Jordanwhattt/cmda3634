#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {

    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tag = 999;
    int count = 1;
    
    int offset = size/2;

    int n = 0;
    int ranks_received = 0;
    while(n < size-1) {
        

        

        
        
    }
    
