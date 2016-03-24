/************************************
* Queue implementation by Al Kelley
* and Ira Pohl -- 1998
* Modified by Michael Kolarik -- 2016
************************************/

#include "queue.h"

// Instantiate the empty queue
void initialize(queue *q)
{
    q -> cnt = 0;
    q -> front = NULL;
    q -> rear = NULL;
}

// Add an element to the back of the queue
void enqueue(data id, data a_time, queue *q)
{
    elem *p;

    p = malloc(sizeof(elem));
    p -> id = id;
    p -> a_time = a_time;
    p -> next = NULL;

    if (!empty(q))
    {
        q -> rear -> next = p;
        q -> rear = p;
    }
    else
        q -> front = q -> rear = p;

    q -> cnt++;
}

// Dequeue the first element in the queue and return it
elem dequeue(queue *q)
{
    data d;
    elem *p;

    d = q -> front -> id;
    p = q -> front;

    q -> front = q -> front -> next;
    q -> cnt--;

    //free(p);
    return *p;
}

// Return front (first) postion in queue
data front(const queue *q)
{
    return (q -> front -> id);
}

// Determine if the queue is empty
boolean empty(const queue *q)
{
    return ((boolean) (q -> cnt == EMPTY));
}

// Determine if the queue is full
boolean full(const queue *q)
{
    return ((boolean) (q -> cnt == FULL));
}
