#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <pthread.h>

typedef struct {
    double a;
    double b;
    int n;
    int thread_count;
} IntegralParams;

typedef struct {
    double a;
    double b;
    int n;
    double result;
} ThreadArgs;

double f(double x);
double integrate(double a, double b, int n);
void *thread_integrate(void *args);
double parallel_integrate(double a, double b, int n, int thread_count);

#endif
