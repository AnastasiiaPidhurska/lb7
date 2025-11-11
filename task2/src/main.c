#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../include/array_rw.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int size = 10;
    int writer_count = 2;
    int reader_count = 4;
    int run_time = 10; 

    if (argc > 1) size = atoi(argv[1]);

    SharedArray array;
    init_array(&array, size);

    pthread_t writers[writer_count];
    pthread_t readers[reader_count];
    pthread_t monitor;

   
    for (int i = 0; i < writer_count; i++)
        pthread_create(&writers[i], NULL, writer_thread, &array);

    for (int i = 0; i < reader_count; i++)
        pthread_create(&readers[i], NULL, reader_thread, &array);

    pthread_create(&monitor, NULL, monitor_thread, &array);

 
    sleep(run_time);
    array.running = 0;

  
    for (int i = 0; i < writer_count; i++)
        pthread_join(writers[i], NULL);

    for (int i = 0; i < reader_count; i++)
        pthread_join(readers[i], NULL);

    pthread_join(monitor, NULL);

    destroy_array(&array);
    printf("Program finished.\n");

    return 0;
}
