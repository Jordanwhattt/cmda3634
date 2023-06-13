#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){

    long long int H = 0;
    long long int N = strtod(argv[1], NULL);

    clock_t tic, toc;
    double elapsed = 0;

    tic = clock();

    for(int i=0;i<N;++i){
        float x = drand48();
        float y = drand48();
        H += (x*x+y*y<1);
    }

    toc = clock();

    elapsed = (toc-tic)/(double)CLOCKS_PER_SEC;

    printf("N = %lld\n", N);
    printf("pi ~ %17.15lf\n", H*(4.)/N);
    printf("elapsed ~ %lg s\n", elapsed);
}

