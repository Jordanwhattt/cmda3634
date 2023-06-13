
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

//This function does not need to be named this, but kernel is added to remind us this process will take place on the GPU
// nvcc -o cudaHelloRank cudeHelloRank.cu
__global__ void fillVectorKernel(int N, double *x) {

    int thread = threadIdx.x;
    int block = blockIdx.x;
    int dim = blockDim.x;   //number of threads per block
    int grid = gridDim.x;   //number of blocks
    
    int n = thread + block*dim; // n in range [0,grid*dim)

    while(n<N) {
        x[n] = n;
        n += grid*dim;
    }

}


int main(int argc, char** argv) {
    
    int G = 4; // 10 thread blocks
    int B = 64; //20 threads per thread-block

    int N = 100000; //pass this number into the function
    double *c_x;
    double *h_x = (double*) calloc(N, sizeof(double));

    cudaMalloc(&c_x, N*sizeof(double));

    fillVectorKernel <<< G, B >>> (N, c_x);

    cudaMemcpy(h_x, c_x, N*sizeof(double), cudaMemcpyDeviceToHost);
    
    int n;
    for(n = 0; n < N;n++) {
        printf("h_x[%d] = %f\n", n, h_x[n]);
    } 
    cudaFree(c_x);
    
}
