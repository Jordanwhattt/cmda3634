#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main(int argc, char **argv) {

	int nthreads = 4;

	omp_set_num_threads(nthreads);
	
#pragma omp parallel
{
	long long int H = 0;
	long long int N = strtod(argv[1], NULL);

	clock_t tic, toc;
	
	double x, y = 1;
	
	struct drand48_data seed;

	srand48_r(omp_get_thread_num(), &seed);

	double elapsed = 0;

	tic = clock();
	int i;
	for(i = 0; i < N; ++i) {
		double x, y;
		drand48_r(&seed, &x);
		drand48_r(&seed, &y);
		H += (x*x + y*y < 1);
	}

	toc = clock();

	elapsed = (toc-tic)/(double)CLOCKS_PER_SEC;

	printf("N = %lld\n", N);
	printf("pi ~ %17.15lf\n", H*(4.)/N);
	printf("elapsed ~ %lg s\n", elapsed);
}

return 0;
}

