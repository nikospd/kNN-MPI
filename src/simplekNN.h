#ifndef VPTREE_H
#define VPTREE_H

typedef struct knnresult{
	int * nidx; //Indices (0-based) of nearest neghbors [m-by-k]
	double * ndist; //Distances of nearest neighbors [m-by-k]
	int m; //Number of query points
  int k; //Number of nearest neighbors
}knnresult;

knnresult kNN(double *X, double *Y, int n, int m, int d, int k);


#endif
