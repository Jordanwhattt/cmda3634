/*
main.c by Jonathan Baker

This code is for "part 2" of the Fuzzy Lloyd project.

You can study and modify this file to meet the requirements of part and 3.
*/

#include <stdlib.h>
#include <stdio.h>
#include "fuzzykmeans.h"
#include "oracle.h"
#include <mpi.h>

int main(int carg,char** varg){
    int rank, p;

    MPI_Init(&carg, &varg);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(carg != 4){
        printf("Please provide three arguments: n k r\n");
        return 1;
    }
    //Total number of data points
    int total = atoi(varg[1]);
    int k = atoi(varg[2]);
    int r = atoi(varg[3]);
    int n = (total + p - 1) / p;
    // total/p data points in one thread. One thread is responsible for n points.
    //int n = total / p;

    if(n<=0 || k<=0 || r < 0){
        printf("n k or r really need to be positive\n");
        return 1;
    }

    double* data = malloc(2*n*sizeof(double));
    double* centers = malloc(2*k*sizeof(double));
    
    

    oracle(data,rank * n ,n);
    
    double send_xlo = data[0];
    double send_xhi = data[0];
    double send_ylo = data[1];
    double send_yhi = data[1];

    int i;
    // Find the rectangle that bounds the data
    for(i=0;i<n;++i){
        if(data[2*i] < send_xlo)
            send_xlo = data[2*i];
        if(data[2*i] > send_xhi)
            send_xhi = data[2*i];
        if(data[2*i+1] < send_ylo)
            send_ylo = data[2*i+1];
        if(data[2*i+1] > send_yhi)
            send_yhi = data[2*i+1];
    }
    //The reductions with MPI_MIN gets the min xlo and ylo of ALL the threads and returns the results to every threads' xlo and ylo variables'
    //The reductions with MPI_MAX gets the max xhi and yhi of ALL the threads and returns the results to every thread's xhi and yhi variables'
    double xlo, xhi, ylo, yhi;
    
    MPI_Reduce(&send_xlo, &xlo, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD); 
    MPI_Reduce(&send_xhi, &xhi, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&send_ylo, &ylo, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);   
    MPI_Reduce(&send_yhi, &yhi, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Select random points in the rectangle for the initial centers
    if(rank == 0) {
        double dx = xhi-xlo;
        double dy = yhi-ylo;
        drand48();
        for(i=0;i<k;++i){
            centers[2*i  ] = drand48()*dx + xlo;
            centers[2*i+1] = drand48()*dy + ylo;
        }
    }

    MPI_Bcast(&centers, 2*k, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Status status;
    if(r == 0 ) {
        double tic, toc;
        tic = MPI_Wtime();

        fuzzykmeans(data,n,centers,k);
    
        toc = MPI_Wtime();
        if(rank==0)
            printf("run time for %d threads: %f\n", p, toc - tic );

    } else if(r == 1) {
        if(rank > 0) {
            // Print the data and converged centers
            MPI_Recv(data, 2 * n, MPI_DOUBLE, rank - 1, 999, MPI_COMM_WORLD, &status);
        }
        if(rank == 0) 
            printf("data = [%lf , %lf,\n",data[0],data[1]);
        for(i=1;i<n;++i)
            printf("        %lf , %lf,\n",data[2*i],data[2*i+1]);
        if(rank < p - 1) {
            MPI_Send(data, 2 * n , MPI_DOUBLE, rank + 1, 999, MPI_COMM_WORLD);    
        }
        if(rank == 0 ) {
            printf("];\ncenters = [%lf , %lf,\n",centers[0],centers[1]);
            for(i=1;i<k;++i)
                printf("           %lf , %lf,\n",centers[2*i],centers[2*i+1]);
            printf("];\n");
        }
    } else {
        printf("r should really be 0 or 1\n");
    }
    free(data);
    free(centers);
    MPI_Finalize();   
    return 0;
}

