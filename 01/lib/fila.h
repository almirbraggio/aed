#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

#define TRUE    1
#define FALSE   0

typedef struct NodeQueue
{
    void *data;
    struct NodeQueue *next;
} NODEQ;

// to store address of front and rear nodes
typedef struct Queue
{
    size_t qsize;
    struct NodeQueue *head;
    struct NodeQueue *tail;
} QUEUE;

// init queue
QUEUE *init_QUEUE (size_t _qsize);

// return true if is empty
int isEmpty_QUEUE (QUEUE *_queue);

// insert element on queue
void insertElement_QUEUE (QUEUE *_queue, const void *_data);

// remove element on queue
void removeElement_QUEUE (QUEUE *_queue, void *_data);

#endif // FILA_H_INCLUDED
