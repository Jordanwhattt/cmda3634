/*
main.c by Jonathan Baker

This code is for "part 2" of the Fuzzy Lloyd project.

You can study and modify this file to meet the requirements of part and 3.
*/

#include <stdlib.h>
#include <stdio.h>
#include "fuzzykmeans.h"
#include "oracle.h"

int main(int carg,char** varg){
    //Make sure there are enough command-line arguments
    if(carg != 4){
        printf("Please provide two arguments: n and k and r\n");
        return 1;
    }
    
    int n = atoi(varg[1]);
    int k = atoi(varg[2]);
    int r = atoi(varg[3]);

    if(n<=0 || k<=0 || r<=0){
        printf("n and k and r really need to be positive\n");
        return 1;
    }

    int rank, size;

    MPI_Init(&carg, &varg);

    //Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    
    
    double* centers = malloc(2*k*sizeof(double));
    
    

    
    
    double xlo = data[0];
    double xhi = data[0];
    double ylo = data[1];
    double yhi = data[1];

    
    // Find the rectangle that bounds the data
    int i;
    for(i=0;i<n;++i){
        if(data[2*i] < xlo)
            xlo = data[2*i];
        if(data[2*i] > xhi)
            xhi = data[2*i];
        if(data[2*i+1] < ylo)
            ylo = data[2*i+1];
        if(data[2*i+1] > yhi)
            yhi = data[2*i+1];
    }

    // Select random points in the rectangle for the initial centers
    double dx = xhi-xlo;
    double dy = yhi-ylo;
    drand48();
    for(i=0;i<k;++i){
        centers[2*i  ] = drand48()*dx + xlo;
        centers[2*i+1] = drand48()*dy + ylo;
    }



    double tic, toc;
    if(r == 0) {
                
        tic = MPI_Wtime();
        
        fuzzykmeans(data,n,centers,k);
        
        toc = MPI_Wtime();
    
    } else if(r == 1) { 
        
        
        // Print the data and converged centers
        printf("data = [%lf , %lf\n",data[0],data[1]);
        for(i=1;i<n;++i) {
            printf("        %lf , %lf\n",data[2*i],data[2*i+1]);
        }
        
        printf("];\ncenters = [%lf , %lf\n",centers[0],centers[1]);
        
        for(i=1;i<k;++i) {
            printf("           %lf , %lf\n",centers[2*i],centers[2*i+1]);
        }
        
        printf("];\n");
    }





    free(data);
    free(centers);

    MPI_Finalize();
    
    return 0;
}

