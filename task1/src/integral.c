#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "../include/integral.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double total_result = 0.0;

double f(double x) {
    return sin(x);
}


double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + h * (i + 0.5);
        sum += f(x);
    }
    return sum * h;
}


void *thread_integrate(void *args) {
    ThreadArgs *data = (ThreadArgs *)args;
    double local_result = integrate(data->a, data->b, data->n);

    pthread_mutex_lock(&mutex);
    total_result += local_result;
    pthread_mutex_unlock(&mutex);

    free(data);
    return NULL;
}

double parallel_integrate(double a, double b, int n, int thread_count) {
    pthread_t threads[thread_count];
    double range = (b - a) / thread_count;

    for (int i = 0; i < thread_count; i++) {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args->a = a + i * range;
        args->b = args->a + range;
        args->n = n / thread_count;

        pthread_create(&threads[i], NULL, thread_integrate, args);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return total_result;
}
