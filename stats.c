#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

// Divide the total number of customers served by the total time open
float calc_avg_wait (int total_customers, int total_time)
{
    return (float)(total_time / total_customers);
}

// Return a new max wait if greater than previous
int calc_max_wait (int new, int current_max)
{
  return (new > current_max) ? new : current_max;
}

// Return a new max queue length if greater than previous
int calc_max_length (queue *customers, int current_max)
{
  return (customers -> cnt > current_max) ? customers -> cnt : current_max;
}

// Return average line length once per minute for each minute
float calc_avg_line_length(queue *customers, int minutes)
{
  return (float)(customers -> cnt / minutes);
}
