#include "knnring.h"
#include <stdlib.h>
#include <stdio.h>
#include "mpi/mpi.h"
#include <time.h>
int main(){
    int n = 20000; //number of data points
    int d = 2; //number of data dimentions 
    int k = 5; //the number of neighbors

    MPI_Init(NULL, NULL);
    int pid,nproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    n = n/nproc; //the number of data points must process
    // printf("MAIN | process number: %d, with total processes: %d and n: %d\n", pid, nproc, n);
    //create the dataset of each process
    double *X = malloc(n*d*sizeof(double));   
    for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			X[d*i+j] = drand(1,1000);
		}
	}
    // printBalk(X, n, d);
    // each process will start the distrAllkNN with it's own dataset -> original dataset / num of processes
    // clock_t begin = clock();
    knnresult r=distrAllkNN(X,n,d,k);
    free(X);
    // printf("MAIN END | process number: %d, with total processes: %d \n", pid, nproc);
    // printBalkInt(r.nidx, n, k);
    free(r.nidx);
    free(r.ndist);
    MPI_Finalize();   
    // clock_t end = clock();
	// double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("\nexcecution time: %f\n", time_spent);
    return 0;
}