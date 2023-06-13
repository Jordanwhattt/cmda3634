#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>


int main(int argc, char **argv) {
  
    int rank, size;

    //Initialize the MPI
    MPI_Init(&argc, &argv);
  
    //Find out the ID of this process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  

    //Find out how many MPI Processes there are
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tag = 999;
    int count = 10;

    int below = rank - 1;
    int above = rank + 1;
   

    int* outv = (int*) calloc(count, sizeof(int));
    int* inv = (int*) calloc(count, sizeof(int));
    int n;
    
    for(n = 0; n < count/2; n++) {
        outv[n] = rank;
    }
    for(n = count/2; n < count; n++) {
        outv[n] = rank + 10;
    }

    if(rank != 0 || rank != (size - 1)) {
        MPI_Send(outv,
            count/2,
            MPI_INT,
            below,
            tag,
            MPI_COMM_WORLD);
        
        MPI_Status status1;
        MPI_Recv(inv+5,
            count/2,
            MPI_INT,
            above,
            tag,
            MPI_COMM_WORLD,
            &status1);
    
        MPI_Send(outv+5,
            count/2,
            MPI_INT,
            above,
            tag,
            MPI_COMM_WORLD);
        MPI_Status status2;
        MPI_Recv(inv,
            count/2,
            MPI_INT,
            below,
            tag,
            MPI_COMM_WORLD,
            &status2);
    }
    

    sleep(0.05*rank);
    int i, j;
    
    printf("\nRank %d outv: [", rank);
    for(j = 0; j < count; j++) {
        printf("%d ", outv[j]);
    }
    printf("]\nRank %d inv: [", rank);
    for(j = 0; j < count; j++) {
        printf("%d ", inv[j]);
    }
    printf("]\n");



    free(outv);
    free(inv);
    MPI_Finalize();
}













