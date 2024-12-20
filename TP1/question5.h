#ifndef QUESTION5_H
#define QUESTION5_H

#include <time.h>

void measure_execution_time(const struct timespec *start, const struct timespec *end, long *exec_time);

void display_exit_code_with_time(int status, long exec_time);

#endif

