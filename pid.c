#include "pid.h"
#include <stdlib.h>
#include <stdbool.h>

int allocate_map(void) {
    int map_size = MAX_PID - MIN_PID;
    pid_map = calloc(map_size, sizeof(int));
    if (pid_map == NULL) {
        return -1;
    } else {
        return 1;
    }
}

int allocate_pid(void) {
    int map_size = MAX_PID - MIN_PID;
    for (int i = 0; i < map_size; i++) {
        if (pid_map[i] == 0) {
            pid_map[i] = 1;
            return i + MIN_PID;
        }
    }
    return -1;
}

void release_pid(int pid) {
    pid_map[pid - MIN_PID] = 0;
}
