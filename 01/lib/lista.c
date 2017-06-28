#include "lista.h"

LIST *init_LIST (size_t _lsize)
{
    LIST *l = (LIST*)malloc(sizeof(LIST));

    if (l == NULL)
        exit(EXIT_FAILURE);

    l->head = NULL;
    l->tail = NULL;
    l->lsize = _lsize;

    return (LIST *)l;
}

int isEmpty_LIST (LIST *_list)
{
    if ((_list->head == NULL) && (_list->tail == NULL))
        return TRUE;
    return FALSE;
}

// insert element on list
void insertElementFront_LIST (LIST *_list, const void *_data)
{
    NODEL *n = (NODEL *)malloc(sizeof(NODEL));
    if (n == NULL)
        exit(EXIT_FAILURE);

    n->data = malloc(_list->lsize);
    if (n->data == NULL)
        exit(EXIT_FAILURE);

    n->next = NULL;
    n->prev = NULL;
    memcpy(n->data, _data, _list->lsize);

    if (isEmpty_LIST(_list)) {
        _list->head = _list->tail = n;
    }
    else {
        _list->head->prev = n;
        n->next = _list->head;
        _list->head = n;
    }
    return;
}

void insertElementBack_LIST (LIST *_list, const void *_data)
{
    NODEL *n = (NODEL *)malloc(sizeof(NODEL));
    if (n == NULL)
        exit(EXIT_FAILURE);

    n->data = malloc(_list->lsize);
    if (n->data == NULL)
        exit(EXIT_FAILURE);

    n->next = NULL;
    n->prev = NULL;
    memcpy(n->data, _data, _list->lsize);

    if (isEmpty_LIST(_list)) {
        _list->head = _list->tail = n;
    }
    else {
        _list->tail->next = n;
        n->prev = _list->tail;
        _list->tail = n;
    }
    return;
}

void insertElementPosition_LIST (LIST *_list, const void *_data, int _position)
{
    int i;
    NODEL *aux; //= (NODEL *)malloc(sizeof(NODEL));

    NODEL *n = (NODEL *)malloc(sizeof(NODEL));
    if (n == NULL)
        exit(EXIT_FAILURE);

    n->data = malloc(_list->lsize);
    if (n->data == NULL)
        exit(EXIT_FAILURE);

    n->next = NULL;
    n->prev = NULL;
    memcpy(n->data, _data, _list->lsize);

    if (_position == 0){
        n->next = _list->head;
        _list->head = n;
        return;
    }

    // Percorre até a posição desejada
    aux = _list->head;
    for (i=0; i < _position; i++) {
        aux = aux->next;
    }
    if (aux == NULL) {
        n->prev = _list->tail;
        _list->tail->next = n;
        _list->tail = n;
        return;
    }
    else {
        n->next = aux;
        n->prev = aux->prev;

        n->prev->next = n;
        n->next->prev = n;
    }
    return;
}

// remove element on list
void removeElementFront_LIST (LIST *_list, void *_data)
{
    if (isEmpty_LIST(_list))
        return;

    NODEL *n = _list->head;
    memcpy(_data, n->data, _list->lsize);

    if (_list->head == _list->tail) {
        _list->head = _list->tail = NULL;
    }
    else {
        _list->head = _list->head->next;
        n = _list->head->prev;
        _list->head->prev = NULL;
    }

    free(n->data);
    free(n);

    return;
}

void removeElementBack_LIST (LIST *_list, void *_data)
{
    if (isEmpty_LIST(_list))
        return;

    NODEL *n = _list->tail;
    memcpy(_data, n->data, _list->lsize);

    if (_list->head == _list->tail) {
        _list->head = _list->tail = NULL;
    }
    else {
        _list->tail = _list->tail->prev;
        n = _list->tail->next;
        _list->tail->next = NULL;
    }

    free(n->data);
    free(n);

    return;
}

const void * removeElementPosition_LIST (LIST *_list, int _position)
{
    NODEL *aux = (NODEL *)malloc(sizeof(NODEL));
    NODEL *previous = (NODEL *)malloc(sizeof(NODEL));
    NODEL *next = (NODEL *)malloc(sizeof(NODEL));

    int i = 0;
    aux = _list->head;

    if (_position == 0) {
        _list->head = _list->head->next;
        _list->head->prev = NULL;
        return aux->data;
    }

    // Percorre até a posição desejada
    for (i = 0; i < _position; i++) {
        aux = aux->next;
    }
    if (aux->next == NULL) {
        aux = _list->tail;
        _list->tail = _list->tail->prev;
        _list->tail->next = NULL;
        return aux->data;
    }
    next = aux->next;
    previous = aux->prev;

    next->prev = previous;
    previous->next = next;

    return aux->data;
}
