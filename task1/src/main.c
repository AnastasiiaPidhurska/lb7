#include <stdio.h>
#include <stdlib.h>
#include "../include/integral.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s a b n thread_count\n", argv[0]);
        printf("Example: %s 0 3.14159 1000000 4\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = atoi(argv[3]);
    int thread_count = atoi(argv[4]);

    double result = parallel_integrate(a, b, n, thread_count);
    printf("Result of integration from %.2f to %.2f = %.10f\n", a, b, result);

    return 0;
}
