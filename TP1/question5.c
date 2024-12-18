#include <time.h>
#include "question5.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void measure_execution_time(struct timespec *start, struct timespec *end, long *exec_time)
{
    *exec_time = (end->tv_sec - start->tv_sec) * 1000 + (end->tv_nsec - start->tv_nsec) / 1000000;
}

void display_exit_code(int status, long exec_time)
{
    char buffer[128];
    int length = 0;

    if (WIFEXITED(status))
    {
        length = snprintf(buffer, sizeof(buffer), "[exit:%d|%ldms]\n", WEXITSTATUS(status), exec_time);
    }
    else if (WIFSIGNALED(status))
    {
        length = snprintf(buffer, sizeof(buffer), "[sign:%d|%ldms]\n", WTERMSIG(status), exec_time);
    }
    write(STDOUT_FILENO, buffer, length);
}

