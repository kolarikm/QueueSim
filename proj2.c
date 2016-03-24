/***********************************
* Event Driven Bank Simulation     *
* CIS 361 -- Winter 2016           *
* Author: Michael Kolarik          *
***********************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stats.h"
#include "queue.h"
#include <string.h>
#include <time.h>
#define AVG_SERVICE 2.0
#define MINUTE 60

//Array used for storing input data
int **in_data;

//Customer queue
queue customer_queue;

//Forward function declarations
int new_customers(int r);

//Model a customer coming into the bank
struct customer {
  int id;
  int time_entered;
  int time_served;
};

typedef struct customer customer;

//Dummy customer
customer d;

// Globally accessible counter for number of customers served
int num_served;

// Generate time based on standard distribution
double expdist (double mean)
{
  double r = rand();
  r /= RAND_MAX;
  return -mean * log(r);
}

// Splits a string into 2 tokens, populates an array row from split
void split_str(char *s, int *r)
{
  r[0] = atoi(strtok(s, "\t"));
  r[1] = atoi(strtok(NULL, "\n"));
}

// Fetches the number of lines for the input data for dynamic allocation
// of correct size for array
int get_num_lines()
{
  FILE *fp;
  fp = fopen("proj2.dat", "r");
  char ch;
  int lines = 0;
  while (!feof(fp))
  {
    ch = fgetc(fp);
    if (ch == '\n')
    {
      lines++;
    }
  }
  fclose(fp);
  return lines;
}

// Takes the input data and populates the 2d array
void read_data()
{
  FILE *in;
  char s[20];
  int i = 0;
  in = fopen("proj2.dat", "r");
  while (fgets(s, 20, in) != NULL)
  {
    split_str(s, in_data[i]);
    if (i == 0)
      in_data[i][2] = in_data[i][1];
      else
        in_data[i][2] = (in_data[i-1][2] + in_data[i][1]);
    i++;
  }
  fclose(in);
}

//Returns the teller ready to take a new customer
int find_teller(customer t[], int num)
{
  for (int i = 0; i < num; i++)
  {
    if (t[i].id == 0) {
      return i;
    }
  }
  return -1;
}

// Frees a spot in the teller array when the customer has been served
int check_teller_status (customer tellers[], int num)
{
  for (int i = 0; i < num; i++)
  {
    int r_time = (tellers[i].time_entered - tellers[i].time_served);
    if (r_time == 0)
    {
      tellers[i] = d;
      num_served++;
      return i;
    }
    else
    {
      //Reduce the customer's time remaining at teller by one second
      tellers[i].time_served--;
    }
  }
  return 0;
}

// Simulation a full 480 minute day in increments of one second each iteration
void simulation (int numOfTellers)
{
  initialize(&customer_queue);

  // Array for new customers coming in this minute
  customer tellers[numOfTellers];

  // Create default customer
  d.id = 0;

  // Set number served
  num_served = 1;

  // Set up of stats variables and loop counters
  float avg_line_len = 0;
  int max_lin_len = 0;
  float avg_wait = 0;
  int max_wait = 0;
  int sec = 0;
  int minutes = 0;
  int c_id = 1;
  srand(time(NULL));

  //Loop for one day, 480 minutes times 60 seconds
  for (sec = 0; sec < (480 * 60); sec++) {

    //If the time in seconds is a new minute new customers arrive
    if (sec % MINUTE == 0) {
      minutes++;
      //Determine how many new customers will enter the queue
      int new_rand = rand() % 100 + 1;
      int new_cust = new_customers(new_rand);

      //Generate new customers based on previous random number and place in
      //the teller array
      for (int x = 0; x < new_cust; x++) {
        customer c;
        c.id = ++c_id;
        c.time_entered = sec;  //Time when entered queue
        c.time_served = sec;   //Changes when dequeued for calculations


        //Every minute need to enqueue the new customers
        enqueue(c.id, sec, &customer_queue);
      }

      //Need to check lengths and wait times every second since
      //customers may be moving around
      max_lin_len = calc_max_length(&customer_queue, max_lin_len);
      avg_line_len = calc_avg_line_length(&customer_queue, minutes);
      avg_wait = calc_avg_wait(num_served, sec);
    }

    // If one of the tellers is open place new, dequeue a element, create a customer
    // from that dequeued element for time management
    int open = find_teller(tellers, numOfTellers);
    if (open > -1)
    {
      customer c;
      elem e;
      e = dequeue(&customer_queue);
      int waited_time = e.a_time - sec;
      max_wait = calc_max_wait(waited_time, max_wait);
      c.id = e.id;
      c.time_entered = e.a_time;
      c.time_served = (int)expdist(AVG_SERVICE);
      tellers[open] = c;
    }
  }

  //Free tellers if the customer has been served before next second begins
  check_teller_status(tellers, numOfTellers);

  //Log all the data for the current simulation
  printf("Results for simulation with %d tellers\n", numOfTellers);
  printf("Total served: %d\n", num_served);
  printf("Average line length: %f\n", avg_line_len);
  printf("Maximum line length: %d\n", max_lin_len);
  printf("Average customer wait time: %f\n", avg_wait);
  printf("Maximum customer wait time: %d\n\n", max_wait);
}

// Determine the number of new customers to generate based on the
// random number passed
int new_customers(int r)
{
  int n = get_num_lines();
  for (int i = 0; i < n; i++)
  {
    if (r <= in_data[i][2])
      return in_data[i][0];
  }
  return 0;
}

int main ()
{
  int l = get_num_lines();

  //Allocate data array
  in_data = (int**)malloc(l * sizeof(int*));
  for (int x = 0; x < l; x++)
  {
    in_data[x] = (int*)malloc(3 * sizeof(int));
  }

  read_data();

  simulation(7);
  simulation(6);
  simulation(5);
  simulation(4);

  free(in_data);
  return 0;
}
