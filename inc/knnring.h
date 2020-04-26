#ifndef VPTREE_H
#define VPTREE_H

typedef struct knnresult{
	int * nidx; //Indices (0-based) of nearest neghbors [m-by-k]
	double * ndist; //Distances of nearest neighbors [m-by-k]
	int m; //Number of query points
  int k; //Number of nearest neighbors
}knnresult;

//! Compute k nearest neighbors of each point in X [n-by-d]
/*!

  \param X	Corpus data points		[n-by-d]
  \param Y	Query data points		[m-by-d]
  \param n	Number of corpus points [scalar]
  \param m	Number of query points	[scalar]
  \param d	Number of dimensions	[scalar]
  \param k	Number of neighbors		[scalar]
  \return The kNN result
*/
knnresult kNN(double *X, double *Y, int n, int m, int d, int k);

//! Compute distributed all-kNN of points in X
/*!

  \param X	Data points				[n-by-d]
  \param n	Number of data points 	[scalar]
  \param d	Number of dimensions	[scalar]
  \param k	Number of neighbors		[scalar]
  \return The kNN result
*/
knnresult distrAllkNN(double * X, int n, int d, int k);

double drand ( double low, double high );
void printBalk(double *X, int N, int D);
void printBalkInt(int *X, int N, int D);

#endif
