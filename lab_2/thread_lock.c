#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "common.h"
#include "thread_lock.h"

pthread_rwlock_t *rwlocks;

void init_locks(int num_strings) {
    rwlocks = malloc(num_strings * sizeof(pthread_rwlock_t));
    for (int i = 0; i < num_strings; i++) {
        pthread_rwlock_init(&rwlocks[i], NULL);
    }
}

void destroy_locks(int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        pthread_rwlock_destroy(&rwlocks[i]);
    }
    free(rwlocks);
}

void read_content(char *dst, int pos, char **theArray) {
    pthread_rwlock_rdlock(&rwlocks[pos]);
    getContent(dst, pos, theArray);
    pthread_rwlock_unlock(&rwlocks[pos]);
}

void write_content(char *src, int pos, char **theArray) {
    pthread_rwlock_wrlock(&rwlocks[pos]);
    setContent(src, pos, theArray);
    pthread_rwlock_unlock(&rwlocks[pos]);
}
