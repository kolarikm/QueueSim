#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stats.h"
#include "queue.h"
#include <string.h>
#include <time.h>
#define AVG_SERVICE 2.0
#define EMPTY 0

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

customer d;

// //Array used to load new customers
// customer *cust_array;

double expdist (double mean)
{
  double r = rand();
  r /= RAND_MAX;
  return -mean * log(r);
}

void split_str(char *s, int *r)
{
  r[0] = atoi(strtok(s, "\t"));
  r[1] = atoi(strtok(NULL, "\n"));
}

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
    printf("%d   %d   %d\n", in_data[i][0], in_data[i][1], in_data[i][2]);
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

/*
int check_tellers()
checks the teller array (which is actually an array of customers numoftellers long)
when a customer is enqueued set a "time to serve" as an expdist that way when you
check for completion you can just check that time against when they were served
time when put in teller array - time to serve == 0, set that array location to -1
next time find teller loops it will catch the empty space and dequeue another customer
*/

int check_tellers(customer tellers[], int num)
{
  for (int i = 0; i < num; i++)
  {
    int r_time = (tellers[i].time_entered - tellers[i].time_served);
    if (r_time == 0)
    {
      tellers[i] = d;
      return i;
    }
    else
    {
      tellers[i].time_served--;
    }
  }
  return 0;
}

void simulation (int numOfTellers)
{
  initialize(&customer_queue);

  // Array for new customers coming in this minute
  customer tellers[numOfTellers];

  // Create default customer
  d.id = 0;

  printf("%d\n", customer_queue.cnt);
  int cust_served = 0;
  int avg_line_len = 0;
  int max_lin_len = 0;
  float avg_wait = 0;
  float max_wait = 0;
  int sec, min;
  int c_id = 1;
  srand(time(NULL));

  //Loop for one day, 480 minutes times 60 seconds
  for (sec = 0; sec < (480 * 60); sec++) {

    if (sec % 60 == 0) {

      //Determine how many new customers will enter the queue
      int new_rand = rand() % 100 + 1;
      int new_cust = new_customers(new_rand);

      //Generate new customers based on previous random number and place in
      //the teller array
      for (int x = 0; x < new_cust; x++) {
        customer c;
        c.id = ++c_id;
        c.time_entered = sec;           //Time when entered queue
        c.time_served = sec;             //NEEDS TO CHANGE SET to time when dequeued


        //Every time you enqueue check queue.cnt against current max update if necces
        enqueue(c.id, sec, &customer_queue);
        max_lin_len = calc_max_length(&customer_queue, max_lin_len);

        //printf("Teller & id %d\n", tellers[x].id);

        //printf("id in q: %d\n", c.id);
      }



      //check_tellers(  :-)  )
      //Check if there is an empty space in teller array, if so, that empty space = dequeue(&customer_queue);

    }

    // If one of the tellers is open place dequeue a element, create a customer
    // from that dequeued element for time management
    int open = find_teller(tellers, numOfTellers);
    if (open > -1)
    {
      customer c;
      elem e;
      e = dequeue(&customer_queue);
      c.id = e.id;
      c.time_entered = e.a_time;
      c.time_served = sec;
      tellers[open] = c;
    }
  }

  //Somehow need to simulate 480 separate minutes
  //Use expdist to figure out how long serving that customer takes for each teller
  //One queue with 1-100 new elems getting added every 60 ticks
  //Each teller can handle 60 / that teller's expdist number of customers per tick
  //enqueue(cust_id, a_time, &q); cust_id++ after every enqueue
}

int new_customers(int r)
{
  //int n = sizeof(percent_range) / sizeof(int);
  int n = get_num_lines();
  //printf("Size of array: %d\n", n);
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

  customer c1;
  c1.id = 1;
  printf("Customer: %d\n", c1.id);
  // cust_array = (customer*)malloc(10000 * sizeof(c1));

  simulation(7);
  printf("100: %d\n", new_customers(100));
  printf("65: %d\n", new_customers(65));
  printf("37: %d\n", new_customers(37));
  printf("20: %d\n", new_customers(20));
  printf("4: %d\n", new_customers(4));

  // double t = expdist(AVG_SERVICE);
  // double r = expdist(AVG_SERVICE);
  // double u = expdist(AVG_SERVICE);
  //
  // printf("%f\n", t);
  // printf("%f\n", r);
  // printf("%f", u);
  free(in_data);
  return 0;

}
