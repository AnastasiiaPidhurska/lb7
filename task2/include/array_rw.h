#ifndef ARRAY_RW_H
#define ARRAY_RW_H

#include <pthread.h>

typedef struct {
    int *arr;
    int size;
    pthread_rwlock_t lock;
    int running;
} SharedArray;

void init_array(SharedArray *a, int size);
void destroy_array(SharedArray *a);
void *writer_thread(void *arg);
void *reader_thread(void *arg);
void *monitor_thread(void *arg);

#endif
