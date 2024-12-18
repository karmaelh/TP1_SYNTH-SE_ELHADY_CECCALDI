#ifndef QUESTION5_H
#define QUESTION5_H

#include <time.h>

void measure_execution_time(struct timespec *start, struct timespec *end, long *exec_time);
void display_exit_code(int status, long exec_time);

#endif
