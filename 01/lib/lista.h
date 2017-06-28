#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

#define TRUE    1
#define FALSE   0

typedef struct NodeList
{
    void *data;
    struct NodeList *next;
    struct NodeList *prev;
} NODEL;

// to store address of front and rear nodes
typedef struct List
{
    size_t lsize;
    struct NodeList *head;
    struct NodeList *tail;
} LIST;

// init list
LIST *init_LIST (size_t _lsize);

// return true if is empty
int isEmpty_LIST (LIST *_list);

// insert element on list
void insertElementFront_LIST (LIST *_list, const void *_data);
void insertElementBack_LIST (LIST *_list, const void *_data);
void insertElementPosition_LIST (LIST *_list, const void *_data, int _position);

// remove element on list
void removeElementFront_LIST (LIST *_list, void *_data);
void removeElementBack_LIST (LIST *_list, void *_data);
const void * removeElementPosition_LIST (LIST *_list, int _position);

#endif // LISTA_H_INCLUDED
