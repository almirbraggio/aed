#include "fila.h"

QUEUE *init_QUEUE (size_t _qsize)
{
    QUEUE *q = (QUEUE*)malloc(sizeof(QUEUE));

    if (q == NULL)
        exit(EXIT_FAILURE);

    q->head = NULL;
    q->tail = NULL;
    q->qsize = _qsize;

    return (QUEUE *)q;
}

int isEmpty_QUEUE (QUEUE *_queue)
{
    if ((_queue->head == NULL) && (_queue->tail == NULL))
        return TRUE;
    return FALSE;
}

// insert element on queue
void insertElement_QUEUE (QUEUE *_queue, const void *_data)
{

    NODEQ *n = (NODEQ *)malloc(sizeof(NODEQ));
    if (n == NULL)
        exit(EXIT_FAILURE);

    n->data = malloc(_queue->qsize);
    if (n->data == NULL)
        exit(EXIT_FAILURE);

    n->next = NULL;
    memcpy(n->data, _data, _queue->qsize);

    if (isEmpty_QUEUE(_queue)) {
        _queue->head = _queue->tail = n;
    }
    else {
        _queue->tail->next = n;
        _queue->tail = n;
    }

    return;
}

// remove element on queue
void removeElement_QUEUE (QUEUE *_queue, void *_data)
{
    if (isEmpty_QUEUE(_queue))
        return;

    NODEQ *n = _queue->head;
    memcpy(_data, n->data, _queue->qsize);

    if (_queue->head == _queue->tail) {
        _queue->head = _queue->tail = NULL;
    }
    else {
        _queue->head = _queue->head->next;
    }

    free(n->data);
    free(n);

    return;
}
