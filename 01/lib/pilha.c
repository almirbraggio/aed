#include "pilha.h"

STACK *init_STACK (size_t _qsize)
{
    STACK *s = (STACK*)malloc(sizeof(STACK));

    if (s == NULL)
        exit(EXIT_FAILURE);

    s->head = NULL;
    s->qsize = _qsize;

    return (STACK *)s;
}

int isEmpty_STACK (STACK *_stack)
{
    if (_stack->head == NULL)
        return TRUE;
    return FALSE;
}

// insert element on stack
void pushElement_STACK (STACK *_stack, const void *_data)
{

    NODES *n = (NODES *)malloc(sizeof(NODES));
    if (n == NULL)
        exit(EXIT_FAILURE);

    n->data = malloc(_stack->qsize);
    if (n->data == NULL)
        exit(EXIT_FAILURE);

    n->next = _stack->head;
    memcpy(n->data, _data, _stack->qsize);

    _stack->head = n;

    return;
}

// remove element on stack
void popElement_STACK (STACK *_stack, void *_data)
{
    if (isEmpty_STACK(_stack))
        return;

    NODES *n = _stack->head;
    memcpy(_data, n->data, _stack->qsize);

    _stack->head = _stack->head->next;

    free(n->data);
    free(n);

    return;
}
