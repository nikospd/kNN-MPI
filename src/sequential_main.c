#include <knnring.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n=20000, m=20000, d=2, k=5;
	double* X = malloc(n*d*sizeof(double));
	double* Y = malloc(m*d*sizeof(double));
	for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			X[d*i+j] = drand(1,100);
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<d;j++){
			Y[d*i+j] = drand(1,100);
		}
	}

	// printBalk(X, n, d);
	// printBalk(Y, m, d);

	clock_t begin = clock();
	knnresult result = kNN(X, Y, n, m, d, k);
	// printBalk(result.ndist, m, k);
	// printBalkInt(result.nidx, m, k);
	free(result.ndist); 
	free(result.nidx);
	free(X);
	free(Y);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nexcecution time: %f\n", time_spent);
	return 0;
}