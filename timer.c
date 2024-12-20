#include <time.h>
#include <stdio.h>
#include "timer.h"

#define NANO_TO_MILLI 1000000

void start_timer(struct timespec *start) {
    if (clock_gettime(CLOCK_MONOTONIC, start) == -1) {
        perror("clock_gettime (start)");
    }
}

void stop_timer(struct timespec *start, struct timespec *end) {
    if (clock_gettime(CLOCK_MONOTONIC, end) == -1) {
        perror("clock_gettime (end)");
    }
}

long calculate_duration_ms(const struct timespec *start, const struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * 1000 +
           (end->tv_nsec - start->tv_nsec) / NANO_TO_MILLI;
}

