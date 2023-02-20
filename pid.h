#include <sys/types.h>

// Do not modify the MIN_PID and MAX_PID variables
#define MIN_PID 300
#define MAX_PID 310 // exclusive

int* pid_map;

// You can declare other important variables and/or structures here
int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
