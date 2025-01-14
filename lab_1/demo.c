#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lab1_IO.h"
#include "timer.h"

typedef struct {
    int **A, **B, **C;
    int size;
    int start;
    int end;
} thread_data;

void *matrix_multiply(void *arg) {
    thread_data *data = (thread_data *)arg;

    for (int i = data->start; i <= data->end; i++) {
        for (int j = 0; j < data->size; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->size; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }

    return NULL;
}

int main() {
    int **A, **B, **C;
    int size, num_threads;
    double start, end;

    // Intialize matrices
    if (Lab1_loadinput(&A, &B, &size)) {
        return -1;
    }

    C = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        C[i] = malloc(size * sizeof(int));
    }

    // Initialize threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    if (num_threads <= 0 || num_threads > size) {
        printf("Invalid number of threads. Must be between 1 and %d.\n", size);
        return -1;
    }

    pthread_t threads[num_threads];
    thread_data thread_data_array[num_threads];
    int row_column_per_thread = size / num_threads;
    int remainder = size % num_threads;
    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data_array[i].A = A;
        thread_data_array[i].B = B;
        thread_data_array[i].C = C;

        thread_data_array[i].size = size;

        thread_data_array[i].start = current_row;
        thread_data_array[i].end = current_row + row_column_per_thread - 1;

        if (i < remainder) {
            thread_data_array[i].end += 1;
        }

        current_row = thread_data_array[i].end + 1;
    }

    // Multiply matrices
    GET_TIME(start);

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_data_array[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    GET_TIME(end);

    printf("Execution time: %f\n", end - start);

    if (Lab1_saveoutput(C, &size, end - start)) {
        return -1;
    }

    return 0;
}