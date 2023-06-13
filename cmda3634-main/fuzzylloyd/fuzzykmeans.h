
#ifndef fkm_h
#define fkm_h

// "v0" and "v1" are pointers, each representing an array with 2 elements.
//
// Returns the SQUARED Euclidean distance
// between the points ( v0[0] , v0[1] ) and ( v1[0] , v1[1] ).
double dist2(double* v0, double* v1);

// Calculate the weight between data point i and center j (wij)
// "vi" is an pointer to a single data point (number i).
// "centers" is an array of length 2*k (coordinates of ALL cluster centers).
// "j" is the index of the cluster center whose weight should be calculated.
// "k" is the number of cluster centers.
//
// Returns the weight of data point vi respect to cluster j.
double weight(double* vi,double* centers,int j,int k);

// "data" is an array of length 2*n (coordinates of data points).
// "centers" is an array of length 2*k (coordinates of cluster centers).
//
// Instead of returning anything, this function overwrites memory in the "centers" array.
// The cluster centers are updated with one iteration of fuzzy Lloyd's algorithm.
void fuzzykmeans(double* data, int n, double* centers, int k);

#endif

