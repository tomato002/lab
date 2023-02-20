#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "pid.c"

void *processThread(void *thread_id) {
    int id = *(int *) thread_id;
    int pid = allocate_pid();
    if (pid == -1) {
        printf("Unable to allocate pid for thread %d\n", id);
        return NULL;
    }
    printf("Allocated PID: %d for thread %d\n", pid, id);
    printf("Sleeping for a while... \n");
    sleep(rand() % 10);
    printf("Releasing PID: %d for thread %d\n", pid, id);
    release_pid(pid);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./manager <number of threads>\n");
        return 1;
    }
    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Invalid number of threads\n");
        return 1;
    }
    if (num_threads >= MAX_PID - MIN_PID) {
        printf("Number of threads must be less than available pids\n");
        return 1;
    }
    allocate_map();
    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, processThread, (void *) &thread_ids[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("All good, bye!\n");
    return 0;
}
