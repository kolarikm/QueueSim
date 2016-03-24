#include "queue.h"

void initialize(queue *q)
{
    q -> cnt = 0;
    q -> front = NULL;
    q -> rear = NULL;
}

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

data front(const queue *q)
{
    return (q -> front -> id);
}

boolean empty(const queue *q)
{
    return ((boolean) (q -> cnt == EMPTY));
}

boolean full(const queue *q)
{
    return ((boolean) (q -> cnt == FULL));
}
