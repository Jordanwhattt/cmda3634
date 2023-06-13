#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


/* To compile: 
   gcc -fopenmp -o ompSum ompSum.c -lm 
   
   To run with 10000 values:
   ./ompSum 10000 
*/

/* serial */
double sumSerial(int N, double *a){

  double s = 0;
  int n;

  for(n=0;n<N;++n){
    s = s+a[n];
  }

  printf("sumSerial  computes sum %f\n", s);
  
  return s;  
}

/* all threads update shared variable */
double sumParallelForShared(int N, double *a){
  /* BAD CODE - causes race condition */
  double s = 0;
  int n;

#pragma omp parallel for shared(s)
  for(n=0;n<N;++n){
    s = s+a[n];
  }

  printf("sumParallelFor          computes sum %f\n", s);
  
  return s;
}

double sumParallelForCritical(int N, double *a){
  /* CORRECT CODE - slowed by critical condition */
  double s = 0;
  int n;

#pragma omp parallel for shared(s)
  for(n=0;n<N;++n){
#pragma omp critical
    s = s+a[n];
  }

  printf("sumParallelForCritical  computes sum %f\n", s);
  
  return s;
}

double sumParallelForAtomic(int N, double *a){
  /* GOOD CODE - slowed by atomics */
  double s = 0;
  int n;

#pragma omp parallel for shared(s)
  for(n=0;n<N;++n){
#pragma omp atomic
    s = s+a[n];
  }

  printf("sumParallelForAtomic    computes sum %f\n", s);
  
  return s;
}


double sumParallelForReduction(int N, double *a){
  /* GOOD CODE */
  double s = 0;
  int n;

#pragma omp parallel for reduction(+:s) schedule(dynamic,1024)
  for(n=0;n<N;++n){
    s += a[n];
  }

  printf("sumParallelForReduction computes sum %f\n", s);
  
  return s;
}


int main(int argc, char **argv){

  // read number of entries from command line
  if(argc<3){ printf("Usage: ./ompSum Threads N\n"); return 255;}

  int T = atoi(argv[1]);
  int N = atoi(argv[2]);
  
  double *a = (double*) calloc(N, sizeof(double));
  double s;
  double t0, t1, t2, t3, t4, t5;

  omp_set_num_threads(T);

  // populate array
  int n;
  for(n=0;n<N;++n)
    a[n] = 1;

  t0 = omp_get_wtime();
  
  // sum using serial for loop
  sumSerial(N, a);

  t1 = omp_get_wtime();
  
  // sum using parallel for and shared accumulator
  sumParallelForShared(N, a);

  t2 = omp_get_wtime();
  
  // sum using critical region
  s = sumParallelForCritical(N, a);
  
  t3 = omp_get_wtime();

  // sum using atomic operation
  s = sumParallelForAtomic(N, a);

  t4 = omp_get_wtime();
  
  // sum using reduction clause
  s = sumParallelForReduction(N, a);

  t5 = omp_get_wtime();

  // output timing intervals
  printf("%d, %g %%%% serial                 \n", T, t2-t1);
  printf("%d, %g %%%% parallel for shared    \n", T, t2-t1);
  printf("%d, %g %%%% parallel for critical  \n", T, t3-t2);
  printf("%d, %g %%%% parallel for atomic    \n", T, t4-t3);
  printf("%d, %g %%%% parallel for reduction \n", T, t5-t4);
  
  return 0;
}
