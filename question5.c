#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "question5.h"
#include <string.h>

#define NANO_TO_MILLI 1000000
#define NbOfCaract 11

void measure_execution_time(const struct timespec *start, const struct timespec *end, long *exec_time) {
    // Calculate execution time in milliseconds
    *exec_time = (end->tv_sec - start->tv_sec) * 1000 +
                 (end->tv_nsec - start->tv_nsec) / NANO_TO_MILLI;
}

void display_exit_code_with_time(int status, long exec_time) {
    char buffer[64];

    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        snprintf(buffer, sizeof(buffer), "[exit:%d|%ldms] ", exit_code, exec_time);
    } else if (WIFSIGNALED(status)) {
        int signal = WTERMSIG(status);
        snprintf(buffer, sizeof(buffer), "[sign:%d|%ldms] ", signal, exec_time);
    } else {
        snprintf(buffer, sizeof(buffer), "[unknown|%ldms] ", exec_time);
    }

    // Display the prompt with the status
    write(STDOUT_FILENO, buffer, strlen(buffer));
    write(STDOUT_FILENO, "enseash % ", NbOfCaract);
}