#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../include/array_rw.h"

void init_array(SharedArray *a, int size) {
    a->arr = malloc(size * sizeof(int));
    a->size = size;
    a->running = 1;

    for (int i = 0; i < size; i++)
        a->arr[i] = 0;

    if (pthread_rwlock_init(&a->lock, NULL)) {
        fprintf(stderr, "RWLock init error\n");
        exit(EXIT_FAILURE);
    }
}

void destroy_array(SharedArray *a) {
    pthread_rwlock_destroy(&a->lock);
    free(a->arr);
}


void *writer_thread(void *arg) {
    SharedArray *a = (SharedArray *)arg;
    while (a->running) {
        int index = rand() % a->size;
        int value = rand() % 100;

        pthread_rwlock_wrlock(&a->lock);
        a->arr[index] = value;
        pthread_rwlock_unlock(&a->lock);

        printf("[Writer %lu] arr[%d] = %d\n", pthread_self(), index, value);
        usleep(500000); 
    }
    return NULL;
}


void *reader_thread(void *arg) {
    SharedArray *a = (SharedArray *)arg;
    while (a->running) {
        int index = rand() % a->size;

        pthread_rwlock_rdlock(&a->lock);
        int value = a->arr[index];
        pthread_rwlock_unlock(&a->lock);

        printf("\t[Reader %lu] arr[%d] = %d\n", pthread_self(), index, value);
        usleep(300000);
    }
    return NULL;
}


void *monitor_thread(void *arg) {
    SharedArray *a = (SharedArray *)arg;
    while (a->running) {
        pthread_rwlock_rdlock(&a->lock);
        printf("Array state: ");
        for (int i = 0; i < a->size; i++)
            printf("%d ", a->arr[i]);
        printf("\n");
        pthread_rwlock_unlock(&a->lock);
        sleep(2);
    }
    return NULL;
}
