#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

#define TRUE    1
#define FALSE   0

typedef struct NodeStack
{
    void *data;
    struct NodeStack *next;
} NODES;

// to store address of front and rear nodes
typedef struct Stack
{
    size_t qsize;
    struct NodeStack *head;
} STACK;

// init stack
STACK *init_STACK (size_t _qsize);

// return true if is empty
int isEmpty_STACK (STACK *_stack);

// insert element on stack
void pushElement_STACK (STACK *_stack, const void *_data);

// remove element on stack
void popElement_STACK (STACK *_stack, void *_data);

#endif // PILHA_H_INCLUDED
