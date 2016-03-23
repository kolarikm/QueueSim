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

//Forward function declarations
int new_customers(int r);

//Model a customer coming into the bank
struct customer {
  int id;
  int time_entered;
  int time_served;
};

typedef struct customer customer;

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

void simulation (int numOfTellers)
{
  int cust_served, avg_line_len, max_lin_len;
  float avg_wait, max_wait;
  int sec, min;

  srand(time(NULL));

  //Loop for one day, 480 minutes times 60 seconds
  for (sec = 0; sec < (480 * 60); sec++) {

    if (sec % 60 == 0) {
      //Determine how many new customers will enter the queue
      int new_rand = rand() % 100 + 1;
      int new_cust = new_customers(new_rand);


      //Bring in new customers
      //Random number between 1 and 100, then check its value
      //against data[3] to find number of new customers
      //int new_cust = ^
      //create_new_custs


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
