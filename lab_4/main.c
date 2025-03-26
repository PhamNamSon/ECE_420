#define LAB4_EXTEND

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Lab4_IO.h"
#include "timer.h"
#include <mpi.h>

#define EPSILON 0.00001
#define DAMPING_FACTOR 0.85

int main (int argc, char* argv[]) {
    struct node *nodehead;
    int nodecount;
    double *r, *r_pre;
    int i, j;
    int iterationcount=0;
    double start, end, elapsed;
    FILE *fp;
    int rank, size;
    int *link_array;
    int nodeIndex, nodein, nodeout;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        fp = fopen("data_input_meta", "r");
        if (!fp) {
            printf("Error opening data_input_meta\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        (void)fscanf(fp, "%d\n", &nodecount);
    }

    MPI_Bcast(&nodecount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    link_array = (int*) malloc(nodecount * sizeof(int));

    if (rank == 0) {
        for (i = 0; i < nodecount; i++) {
            (void)fscanf(fp, "%d\t%d\t%d\n", &nodeIndex, &nodein, &nodeout);
            link_array[nodeIndex] = nodeout;
        }
        fclose(fp);
    }

    MPI_Bcast(link_array, nodecount, MPI_INT, 0, MPI_COMM_WORLD);

    int node_per_process = nodecount / size;
    int rem = nodecount % size;

    int *displs = (int *)malloc(size * sizeof(int));
    int *sendcounts = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        sendcounts[i] = node_per_process;
        if (rem > 0) {
            sendcounts[i]++;
            rem--;
        }
        displs[i] = i * node_per_process;
    }

    // printf("nodecount = %d\n", nodecount);
    // printf("node_per_process = %d, rem = %d\n", node_per_process, rem);
    // for (i = 0; i < size; i++) {
    //     printf("displs[%d] = %d, sendcounts[%d] = %d\n", i, displs[i], i, sendcounts[i]);
    // }

    // for (int r = 0; r < size; r++) {
    //     if (rank == r) {
    //         // Print your stuff
    //         printf("Rank %d: node_per_process = %d, rem = %d\n", rank, node_per_process, rem);
    //         fflush(stdout);
    //     }
    // }

    int local_n = sendcounts[rank];
    int local_start = displs[rank];
    int local_end = local_start + local_n;

    // printf("Rank %d: local_n = %d, local_start = %d, local_end = %d\n", rank, local_n, local_start, local_end);

    node_init(&nodehead, local_start, local_end);

    r = (double*) malloc(local_n * sizeof(double));
    r_pre = (double*) malloc(local_n * sizeof(double));

    for (i = 0; i < local_n; i++) {
        r[i] = 1.0 / nodecount;
        // printf("Rank %d: r[%d] = %f\n", rank, i, r[i]);
    }

    double *total_r = (double*) malloc(nodecount * sizeof(double));
    double rel_err;

    GET_TIME(start);

    do {
        iterationcount++;
        vec_cp(r, r_pre, local_n);

        MPI_Allgatherv(r, local_n, MPI_DOUBLE,
                       total_r, sendcounts, displs, MPI_DOUBLE,
                       MPI_COMM_WORLD);

        for (i = 0; i < local_n; i++) {
            double sum = 0.0;
            for (j = 0; j < nodehead[i].num_in_links; j++) {
                int inlink = nodehead[i].inlinks[j];
                if (link_array[inlink] > 0)
                    sum += total_r[inlink] / link_array[inlink];
            }
            r[i] = (1.0 - DAMPING_FACTOR) / nodecount + DAMPING_FACTOR * sum;
        }

        rel_err = rel_error(r, r_pre, local_n);
        MPI_Allreduce(MPI_IN_PLACE, &rel_err, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    } while (rel_err >= EPSILON);

    GET_TIME(end);
    elapsed = end - start;

    MPI_Gatherv(r, local_n, MPI_DOUBLE,
                total_r, sendcounts, displs, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        Lab4_saveoutput(total_r, nodecount, elapsed);
        printf(" Iterations: %d Time: %f seconds.\n", iterationcount, elapsed);
    }

    node_destroy(nodehead, local_n);
    free(r);
    free(r_pre);
    free(total_r);
    free(link_array);
    free(sendcounts);
    free(displs);

    MPI_Finalize();
    return 0;
}
