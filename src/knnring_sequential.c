#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct knnresult{
	int * nidx;
	double * ndist;
	int m;
  int k;
}knnresult;

void quicksort(double *A, int *B, int len) {
  if (len < 2) return;

  double pivot = A[len / 2];

  int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;

    if (i >= j) break;

    double temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;

		int temp2 = B[i];
		B[i] = B[j];
		B[j] = temp2;
  }

  quicksort(A, B, i);
  quicksort(A + i, B + i, len - i);
}

void printBalk(double *X, int N, int D){
	for (int i=0;i<N;i++){
		for (int j=0;j<D;j++){
			printf(" %f || ",*(X+((D*i)+j)));
		}
		printf(" \n");
	}
	printf("-------\n");
}

void printBalkInt(int *X, int N, int D){
	for (int i=0;i<N;i++){
		for (int j=0;j<D;j++){
			printf(" %d || ",*(X+((D*i)+j)));
		}
		printf(" \n");
	}
	printf("-------\n");
}


void queryPointDistances(double* allDistances, double* Ypoint, double* X, int d, int n){
  for(int i=0;i<n;i++){
    double sum=0;
    for (int j=0;j<d;j++){
      sum += pow((Ypoint[j] - X[i*d+j]), 2);
    }
    allDistances[i] = sqrt(sum);
  }
}

void kNNPoints(int* nidxPoint, double* ndistPoint, double* allDistances, int* distancesFirstIndex, int n, int k){
	quicksort(allDistances, distancesFirstIndex, n);
	for(int i=0;i<k;i++){
		nidxPoint[i] = distancesFirstIndex[i];
		ndistPoint[i] = allDistances[i];
  }
}

knnresult kNN(double *X, double *Y, int n, int m, int d, int k){
	int* nidx = malloc(m*k*sizeof(int));
	double* ndist = malloc(m*k*sizeof(double));
	double* allDistances = malloc(n*sizeof(double));//The distances for each point of the query set, with every point of the corpus set
	int* distancesFirstIndex = malloc(n*sizeof(int));
	int* nidxPoint = malloc(k*sizeof(int));
	double* ndistPoint = malloc(k*sizeof(double));
	for(int i=0;i<m;i++){
		
		queryPointDistances(allDistances, &Y[i*d], X, d, n);
		// printBalk(allDistances, n, 1);
		for(int z=0;z<n;z++){
			distancesFirstIndex[z] = z;
		}
		kNNPoints(nidxPoint, ndistPoint, allDistances, distancesFirstIndex, n, k);

		for(int j=0;j<k;j++){
			nidx[i*k+j] = nidxPoint[j];
			ndist[i*k+j] = ndistPoint[j];
		}

		
  	}
	free(nidxPoint);
	free(ndistPoint);

  knnresult node = {.nidx = nidx, .ndist = ndist, .m = m, .k = k};
	free(allDistances);
	free(distancesFirstIndex);
  return node;
}

double drand ( double low, double high )
{
    return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}