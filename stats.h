#include "queue.h"

#ifndef _STATS
#define _STATS

float calc_avg_wait(int total_customers, int total_time);
float calc_avg_line_length(queue *customers, int minutes);
int calc_max_length(queue *customers, int current_max);
int calc_max_wait(int new, int current_max);

#endif
