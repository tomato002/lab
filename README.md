# Laboratory 4

Name: <add your name here>

An operating system's *pid manager* is responsible for managing process identifiers. 
When a process is first created, it's assigned a unique pid by the pid manager. 
The pid is returned to the pid manager when the process completes execution, and the manager may later reassign this pid. 
Process identifiers (pid) were discussed in the "Process Management" section of our Lecture 2 and are also discussed more in-depth in Section 3.3 of the book. 
What is most important here is to recognize that process identifiers must be unique, no two active processes can have the same pid.

For this lab, you need to write your *own* programs, in C language, that simulates the pid manager and some running processes using it.

## Compile

Build the program locally with the following command:

```shell
make
```

## Assignments

### Exercise 1

Write a program that implements a *pid manager*. 
You don't have to worry about creating the processes or anything related to that, your focus should be exclusively on the component of managing the pids. 
This means that you need to work with the structure you think is the most appropriate to solve this problem and any surrounding code to achieve your solution.

Use the following constants to identify the range of possible pid values: 
```c
#define MIN_PID 300 
#define MAX_PID 310 // exclusive
```

You may use any data structure of your choice to represent the availability of process identifiers. 
One strategy is to adopt what Linux has done and use a bitmap in which a value of 0 at position i indicates that a process id of value i is available and a value of 1 indicates that the process id is currently in use. 

Implement the following API for obtaining and releasing a pid:

- Creates and initializes a data structure for representing pids; returns -1 if unsuccessful, 1 if successful.
```c
int allocate_map (void)
```

- Allocates and returns a pid; returns -1 if unable to allocate a pid (e.g., all pids are in use). 
```c
int allocate_pid (void)
```

- Releases a pid.
```c
void release_pid (int pid)
```

You can use the files `pid.h` and `pid.c` as a starting point.


### Exercise 2

Write a program that validates your pid manager by relying on threads. 
You will create a number of threads from a parameter that must be higher than the available number of pids.
This parameter is required and if no parameter is provided it should show an error message but shouldn't fail.
For example, assuming that `MIN_PID 300` and `MAX_PID 310`, ergo you have 10 available pids, this means that you must create more than 10 threads to validate its functionality (e.g. 15, 30, 50).

Each thread will request a pid, sleep for a random period of time between 0 and 10s, and then release the pid. 
On UNIX and Linux systems, sleeping is accomplished through the sleep() function, which is passed an integer value representing the number of seconds to sleep.

This program should validate the following two cases:
- That all pids are used and unique. Since you are using threads, race conditions can and will occur (although sometimes hard to spot).
- That pids rotate once you go beyond the maximum amount of available pids. When pids are released they should be reused immediately or eventually, depends on the implementation but both options are correct.

You can use the file `manager.c` as a starting point.

You can compile it by running:
```shell
gcc -o manager manager.c
./manager 15
# ... proper output
./manager
# ... error message
```

### Exercise 3

Modify the lab by ensuring that the data structure used to represent the availability of the pids is safe from race conditions. 
Use Pthreads mutex locks.
Keep in mind that the critical section should be minimal as discussed in class (Lecture 3).
Failing to do so will impact your grade.

## Docker

To use it with Docker, you first need to build the docker image:

```shell
docker build -t lab4 .
```

Then you can run it like this:
```shell
docker run --rm -ti -v $(pwd)/:/root/lab -w /root/lab lab4 /bin/bash -c "make; ./manager 15"
```

Or you can start a shell inside the container, and then run the commands manually:

```shell
docker run --rm -ti -v $(pwd)/:/root/lab -w /root/lab lab4 /bin/bash
# inside the container
make
./manager 15
```

## Grading

Due to the race condition nature of this lab, auto-grading will not be fully available for this lab.
This means that auto-grading will check that it compiles, and it will check that it runs successfully more than one time.
The output will be used to determine your final grade, so make sure to test it thoroughly.