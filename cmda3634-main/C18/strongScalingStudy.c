#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  
  if(argc!=3){
    printf("usage: ./strongScalingStudy nthreads N\n");
    exit(0);
  }

  // read command line arguments
  int nthreads = atoi(argv[1]);
  int N = atoi(argv[2]);

  // create some storage for results of computation
  double *v = (double*) calloc(N, sizeof(double));

  // create threads
  omp_set_num_threads(nthreads);
  
  double tic, toc;
  int n;
  tic = omp_get_wtime();
  
#pragma omp parallel for
  for(n=0;n<N;++n){
    double x = .1;
    double r = n/(double)N;
    // do 20 logistic map iterations
    int M = 20;
    for(int m=0;m<M;++m){
      x = r*x*(1.-x);
    }
    v[n] = x;
  }

  toc = omp_get_wtime();

  printf("elapsed = %g\n", (toc-tic));
  return 0;

}


