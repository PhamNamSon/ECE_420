#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "thread_lock.h"

#define NUM_STRINGS 5
#define BUFFER_SIZE 100

char *sharedArray[NUM_STRINGS];

void *reader_thread(void *arg) {
    int index = *(int *)arg;
    char buffer[BUFFER_SIZE];
    read_content(buffer, index, sharedArray);
    printf("Reader Thread [%d] Read: %s\n", index, buffer);
    return NULL;
}

void *writer_thread(void *arg) {
    int index = *(int *)arg;
    char msg[BUFFER_SIZE];
    snprintf(msg, BUFFER_SIZE, "Updated Content %d", index);
    write_content(msg, index, sharedArray);
    printf("Writer Thread [%d] Wrote: %s\n", index, msg);
    return NULL;
}

int main() {
    pthread_t readers[NUM_STRINGS], writers[NUM_STRINGS];
    int indices[NUM_STRINGS];

    for (int i = 0; i < NUM_STRINGS; i++) {
        sharedArray[i] = malloc(BUFFER_SIZE * sizeof(char));
        snprintf(sharedArray[i], BUFFER_SIZE, "Initial Content %d", i);
    }

    init_locks(NUM_STRINGS);

    for (int i = 0; i < NUM_STRINGS; i++) {
        indices[i] = i;
        pthread_create(&writers[i], NULL, writer_thread, &indices[i]);
    }

    for (int i = 0; i < NUM_STRINGS; i++) {
        pthread_join(writers[i], NULL);
    }

    for (int i = 0; i < NUM_STRINGS; i++) {
        pthread_create(&readers[i], NULL, reader_thread, &indices[i]);
    }

    for (int i = 0; i < NUM_STRINGS; i++) {
        pthread_join(readers[i], NULL);
    }

    destroy_locks(NUM_STRINGS);

    for (int i = 0; i < NUM_STRINGS; i++) {
        free(sharedArray[i]);
    }

    return 0;
}
