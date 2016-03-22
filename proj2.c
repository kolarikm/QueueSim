#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stats.h"
#include "queue.h"
#include <string.h>
#define AVG_SERVICE 2.0

double expdist (double mean)
{
    double r = rand();
    r /= RAND_MAX;
    return -mean * log(r);
}

void split_str(char *s, int *r)
{
    char * token1;
    char * token2;
    //token1 = strtok(s, "\t");
    //token2 = strtok(NULL, "\n");
    r[0] = atoi(strtok(s, "\t"));
    r[1] = atoi(strtok(NULL, "\n"));
}

void read_data()
{
    FILE *in;
    char s[20];
    int r[5][2];
    int i = 0;
    in = fopen("proj2.dat", "r");
    while (fgets(s, 20, in) != NULL)
    {
        split_str(s, r[i]);
        printf("%d   %d\n", r[i][0], r[i][1]);
        i++;
    }
}

void simulation (int numOfTellers)
{
    int cust_served, avg_line_len, max_lin_len;
    float avg_wait, max_wait;

    //Somehow need to simulate 480 separate minutes
    // !!!  Do this first --> Each minute, calculate random 1-100 number to get number of arriving customers using proj2.dat
            // DONE!  Read in data
            // DONE!  Place into 2d array
            // Write function that takes in a int 1-100 and determines how many customers will be served that minute by looking at number in col2 and then getting and returning col1
    //Use expdist to figure out how long serving that customer takes for each teller
    //One queue with 1-100 new elems getting added every 60 ticks
    //Each teller can handle 60 / that teller's expdist number of customers per tick
    //enqueue(cust_id, a_time, &q); cust_id++ after every enqueue   
}

int main ()
{
    /*
    double t = expdist(AVG_SERVICE);
    double r = expdist(AVG_SERVICE);
    double u = expdist(AVG_SERVICE);

    printf("%f\n", t);
    printf("%f\n", r);
    printf("%f", u);
*/

    read_data();
    return 0;

}
