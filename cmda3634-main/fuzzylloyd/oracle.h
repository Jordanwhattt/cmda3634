
#ifndef ORACLE_H
#define ORACLE_H

// This function provides data.
// Think of it as a file reader for a very large file with two columns of data.
// 
// "data" should be a pointer to a double array of size 2*n.
// "start" is the first line of data you want to read (0 unless you're doing work in parallel)
// The data will be written directly to "data"
void oracle(double* data,long start,long n);

/******************************

THE FUNCTIONS BELOW ARE USED BY THE ORACLE.
YOU DON'T NEED TO USE OR UNDERSTAND THEM.

*******************************/

// Overwrite the seeds, advancing by n iterations
void rand_look_ahead(long n,long* seeds);

// Convert the seeds to a double and
// overwrite seeds with the next value
double rand_advance(long* seeds);

// (b^p) % m
// Suitable for large p
long pow_mod(long b,long p,long m);

#endif


