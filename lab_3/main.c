#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "Lab3IO.h"
#include <math.h>
#include <omp.h>

void swap(double **A, int row1, int row2){
    double *temp = A[row1];
    A[row1] = A[row2];
    A[row2] = temp;
}

int main(int argc, char *argv[]) {
    int num_threads; 
    double start_time, end_time;
    num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Invalid number of threads. Must be greater than 0.\n");
        return -1;
    }

    double **A; 
    int size; 
    if (Lab3LoadInput(&A, &size) != 0) {
        printf("Failed to load input data.\n");
        return 1;
    }

    GET_TIME(start_time);
    int n = size;
    int kp;
    omp_set_num_threads(num_threads);
    for (int k = 0; k < n - 1; k++){
        double max_value = -1;
        kp = k;
        #pragma omp parallel for shared(A, k, max_value, kp)
        for (int i = k; i < n; i++){
            if (fabs(A[i][k]) > max_value){
                #pragma omp critical
                {
                    max_value = fabs(A[i][k]);
                    kp = i;
                }
            }
        }
        swap(A, k, kp);
        #pragma omp parallel for shared(A, k, n)
        for (int i = k+1; i < n; i++){
            double temp = A[i][k] / A[k][k];
            for (int j = k; j < n+1; j++){
                A[i][j] = A[i][j] - (A[k][j] * temp);
            }
        }
    }

    for (int k = n - 1; k >= 1; k--) { 
        #pragma omp parallel for shared(A, k, n)
        for (int i = 0; i < k; i++) {
            A[i][n] = A[i][n] - (A[i][k] / A[k][k]) * A[k][n];
            A[i][k] = 0;
        }
    }



    double *X = CreateVec(n); 
    #pragma omp parallel for shared(A, X, n)
    for (int x = 0; x < n; x++){
        X[x] = A[x][n]/A[x][x];
    }
    GET_TIME(end_time);
    double time = end_time - start_time;
    printf("Time: %f\n", time);
    Lab3SaveOutput(X, n, time);
    DestroyMat(A, n);
    DestroyVec(X);
    return 0; 
}
