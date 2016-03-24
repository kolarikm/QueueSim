#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

float calc_avg_wait (int total_customers, int total_time)
{
    //Divide the total number of customers served by the total time open (480 minutes)
    return (float)(total_time / total_customers);
}

int calc_max_length(queue *customers, int current_max)
{
  if (customers -> cnt > current_max) {
    return customers -> cnt;
  }
  else
  {
    return current_max;
  }
}
