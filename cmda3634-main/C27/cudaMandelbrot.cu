/*

To compile:
make cudaMandelbrot

To run:
./cudaMandelbrot

*/

#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern "C"
{
#include "png_util.h"
}

__global__ void mandelbrotKernel(const int Nx, 
				 const int Ny, 
				 const float xmin,
				 const float ymin,
				 const float dx, 
				 const float dy,
				 float * count){
  
  int n = threadIdx.x + blockDim.x*blockIdx.x;
  int m = threadIdx.y + blockDim.y*blockIdx.y;
  
  const float cx = xmin + n*dx;
  const float cy = ymin + m*dy;
  
  float x = 0;
  float y = 0;
  float xold = 0;
  float yold = 0;
  int Nit = 200;
  int t, cnt=0;
  for(t=0;t<Nit;++t){
    
    // x,y are updated to
    // (x^2 - y^2 + cx, 2*x*y+cre)
    
    // HW17 TASKS:
    // 1. change the update formula using an alternative function in x,y,xold,yold
    //   [ some ideas here: https://math.stackexchange.com/questions/1099/mandelbrot-like-sets-for-functions-other-than-fz-z2c ]
    // 2. zoom in on an interesting feature
    // 3. run the code 
    // 4. use scp to copy the generated png to your laptop
    // 5. upload the png to canvas

    {
      xold = x;
      yold = y;

      float xnew = cx;
      xnew += x*x;
      xnew -= y*y; 
      
      float ynew = cy;
      ynew += 2.f*x*y;
      
      x = xnew;
      y = ynew;
    }

    // check if iterations escaped the radius 2 circle 
    float r = x*x;
    r +=y*y;
    
    if(r<4.f)
      ++cnt;
  }
  
  count[n + m*Nx] = cnt;
  
}


int main(int argc, char **argv){

  int Nx = 4096;
  int Ny = 4096;

  /* box containing sample points */
  float xcent = -.759856;
  float ycent= .125547;
  float diam  = 0.151579;

  /* box is: [xmin,xmax] x [ymin,ymax] */
  float xmin = xcent -0.5*diam;
  float xmax = xcent +0.5*diam;
  float ymin = ycent -0.5*diam;
  float ymax = ycent +0.5*diam;

  float dx = (xmax-xmin)/(Nx-1.f);
  float dy = (ymax-ymin)/(Ny-1.f);
  
  float *h_count = (float*) calloc(Nx*Ny, sizeof(float));
  float *c_count;

  cudaMalloc(&c_count, Nx*Ny*sizeof(float));

  // call mandelbrot from here
  // we will use a thread-block of NTxNT threads
  // every thread will only iterate one point
  int NT = 8;
  dim3 B(NT,NT);
  dim3 G((Nx+NT-1)/NT, (Ny+NT-1)/NT);
  
  cudaEvent_t tic, toc;
  cudaEventCreate(&tic);
  cudaEventCreate(&toc);

  cudaEventRecord(tic);

  mandelbrotKernel <<<G,B>>> (Nx, Ny, xmin, ymin, dx, dy, c_count);

  cudaEventRecord(toc);

  cudaDeviceSynchronize();
  float elapsed;
  cudaEventElapsedTime(&elapsed, tic, toc);
  elapsed/=1000;
  printf("elapsed time %g\n", elapsed);

  // copy data from DEVICE to HOST
  cudaMemcpy(h_count, c_count, Nx*Ny*sizeof(float), cudaMemcpyDeviceToHost);

  // output data from HOST
  FILE *png = fopen("cudaMandelbrot.png", "w");
  write_hot_png(png, Nx, Ny, h_count, 0, 80);
  fclose(png);

}
