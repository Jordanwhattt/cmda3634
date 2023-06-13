// Use OMP to (efficiently) parallelize as many of the loops below as you can.
// If a loop can't be parallelized efficiently,
// then remove the loop with comments.
//
// YOU SHOULD PARALLELIZE AT LEAST 6 LOOPS

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

// Declare functions that will be defined later
float logisticMap(float a,float r);
float logisticLimit(float a,float r);
int randInt();

int main(int argc, char **argv){

    int N = 50;
    int n, i, temp;

    int *v = (int*) malloc(N*sizeof(int));
    int *w = (int*) malloc(N*sizeof(int));
    float *z = (float*) malloc(N*sizeof(float));

    float a0 = 0.2;
    float r = 3.6;

    // Globally set number of threads
    omp_set_num_threads(4);

    // Loop A
    // Fill v with zeros
<<<<<<< HEAD
=======
#pragma omp parallel for
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=0;n<N;++n){
        v[n] = 0;
    }

    // Loop B
    // Propagate value from v[0] to all entries of v
    v[0] = 7;
<<<<<<< HEAD
=======
#pragma omp parallel for shared(v[0])
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=1;n<N;++n){
        v[n] = v[0];
    }

    // Loop C
    // Set v[n] to the nth triangular number
<<<<<<< HEAD
=======
    //Not possible
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=1;n<N;++n){
        if(n==0){
            v[n] = 0;
        }
        else{
            v[n] = v[n-1]+n;
        }
    }

    // Loop D
    // Reverse the entries of v
<<<<<<< HEAD
    for(n=0;n<N/2;++n){ 
=======
#pragma omp parallel for private(temp) shared(v)
    for(n=0;n<N/2;++n){
#pragma omp critical
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
        i = N-1-n;
        temp = v[n];
        v[n] = v[i];
        v[i] = temp;
    }

    // Loop E
    // Store v in reverse order in w
<<<<<<< HEAD
    for(n=0;n<N;++n){
=======
#pragma omp parellel for shared(w)
    for(n=0;n<N;++n){
#pragma omp critical
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
        i = N-1-n;
        w[n] = v[i];
    }

    // Loop F
    // Use randInt() function to fill v with "random" values
    for(n=0;n<N;++n){
        v[n] = randInt();
    }

    // Loop G
    // In z[n], store the nth logistic map iteration of a0 with parameter r
    z[0] = a0;
<<<<<<< HEAD
=======
    //Not possible
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=1;n<N;++n){
        z[n] = logisticMap(z[n-1],r);
    }

    // Loop H
    // In z[n], store an approximate fixed point of the logistic map with parameter 4*n/N
<<<<<<< HEAD
=======
#pragma omp parallel for shared(n)
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=0;n<N;++n){
        z[n] = logisticLimit(a0,4.*n/N);
    }

    // Loop I
    // In v[n], store 1 if n is prime, 0 otherwise
<<<<<<< HEAD
=======
#pragma omp parallel for shared(i, n)
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=0;n<N;++n){
        if(n<2){
            v[n] = 0;
            continue;
        }
        v[n] = 1;
        for(int i=2;i<n/2;++i){
            if(n%i==0){
                v[n] = 0;
                break;
            }
        }
    }

    // Loop J
    // In v[n], store the sum of the first n odd numbers
<<<<<<< HEAD
=======
    //Not possible
>>>>>>> 1bda0e865c42f550ed6453c38d20ef245a4ca9c6
    for(n=0;n<N;++n){
        if(n==0){
            v[n] = 0;
        }
        else{
            v[n] = v[n-1]+2*n-1;
        }
    }

    free(v);
    free(w);
    free(z);
}

/*
   DO NOT MODIFY THESE FUNCTIONS
   You should think of them as library functions
   that are outside of your control.
 */

int x=4;
int T = 30137;
int A = 1;
int M = 65536;
// Return a pseudorandom int
int randInt(){
    x *= T;
    x += A;
    x %= M;
    return x;
}

// Perform one logistic map iteration
float logisticMap(float a,float r){
    return a*(1-a)*r;
}

// Iterate 1000 times to find an approximate periodic point
float logisticLimit(float a,float r){
    for(int i=0;i<1000;++i){
        a = logisticMap(a,r);
    }
    return a;
}

