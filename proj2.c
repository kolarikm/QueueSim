#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stats.h"
#include "queue.h"
#include <string.h>
#include <time.h>
#define AVG_SERVICE 2.0

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
int find_teller(int t[], int num)
{
  for (int i = 0; i < num; i++)
  {
    if (t[i] == -1) {
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

void simulation (int numOfTellers)
{
  initialize(&customer_queue);
  printf("%d\n", customer_queue.cnt);
  int tellers[numOfTellers];
  int cust_served, avg_line_len, max_lin_len;
  float avg_wait, max_wait;
  int sec, min, c_id;
  c_id = 0;
  srand(time(NULL));

  //Loop for one day, 480 minutes times 60 seconds
  for (sec = 0; sec < (480 * 60); sec++) {

    if (sec % 60 == 0) {
      //Determine how many new customers will enter the queue
      int new_rand = rand() % 100 + 1;
      int new_cust = new_customers(new_rand);

      //Create new customers based on previous random number
      for (int x = 0; x < new_cust; x++) {
        customer c;
        c.id = ++c_id;
        c.time_entered = sec;           //Time when entered queue
        c.time_served = sec;             //NEEDS TO CHANGE SET to time when dequeued

        //Every time you enqueue check queue.cnt against current max update if necces
        enqueue(c.id, sec, &customer_queue);
        // printf("id in q: %d\n", c.id);
      }

      //Check if there is an empty space in teller array, if so, that empty space = dequeue(&customer_queue);


    }

    int rr = find_teller(tellers, numOfTellers);
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
