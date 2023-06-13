
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "oracle.h"

void oracle(double* data,long start,long n){
    // I picked randomish seeds. It shouldn't matter much
    long seeds[] = {28470,31023,4437};
    double w;
    int i;

    // Advance the seeds
    // Double the number of values to skip point since
    // each data point takes two random numbers.
    rand_look_ahead(start*2,seeds);

    // To approximate the long term behavior of a random walk,
    // assume that the start steps before we began
    // reached a distance of sqrt(start)/2 from the origin
    w = rand_advance(seeds);
    w *= sqrt(start)/2;
    for(i=0;i<n;++i){
        data[2*i] = w;
        w += rand_advance(seeds)*2-1;
    }

    w = rand_advance(seeds);
    w *= sqrt(start)/2;
    for(i=0;i<n;++i){
        data[2*i+1] = w;
        w += rand_advance(seeds)*2-1;
    }
}

// Based on
// https://en.wikipedia.org/wiki/Wichmann%E2%80%93Hill
void rand_look_ahead(long n,long* seeds){
    const static long m[] = {30269,30307,30323};
    const static long t[] = {171,172,170};

    int i;
    for(i=0;i<3;++i){
        seeds[i] *= pow_mod(t[i],n,m[i]);
        seeds[i] %= m[i];
    }

}

double rand_advance(long* seeds){
    const static long m[] = {30269,30307,30323};
    const static long t[] = {171,172,170};
    int i;
    double sum = 0;
    for(i=0;i<3;++i){
        seeds[i] = seeds[i]*t[i] % m[i];
        sum += (double)seeds[i] / m[i];
    }
    double x = sum - (int)sum;
    return x;
}

long pow_mod(long b,long p,long m){
    if(p == 0)
        return 1;
    long a;
    if(p%2 == 0){
        a = pow_mod(b,p/2,m);
        return a*a % m;
    }
    a = pow_mod(b,p-1,m);
    return a*b % m;
}


