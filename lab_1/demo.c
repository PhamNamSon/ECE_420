#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lab1_IO.h"
#include "timer.h"

int main() {
    int **A, **B, **C;
    int size;
    double start, end;

    if (Lab1_loadinput(&A, &B, &size)) {
        printf("Error loading input matrices.\n");
        return -1;
    }
    return 0;

}