#ifndef TIMER_H
#define TIMER_H

#include <time.h>

// Functions to manage timing
void start_timer(struct timespec *start);
void stop_timer(struct timespec *start, struct timespec *end);
long calculate_duration_ms(const struct timespec *start, const struct timespec *end);

#endif
