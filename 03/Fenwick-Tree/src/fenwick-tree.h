// Author: Almir Braggio

#ifndef FENWICK_TREE_H_INCLUDED
#define FENWICK_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

typedef unsigned char byte;
typedef unsigned int data_t;
typedef struct avltree_node_t *avltree_t;

struct avltree_node_t {
	int key;
	data_t data;
	byte height;
	avltree_t left, right, parent;
};


// init
bintree_t init_bintree (void);

// free
bintree_t free_bintree (bintree_t node);

// empty
bool_t isempty_bintree (bintree_t node);

// insert
bintree_t insert_bintree (bintree_t node, data_t data);

// search
data_t min_bintree (bintree_t node);
data_t max_bintree (bintree_t node);

// prints
void preorder_bintree(bintree_t node);
void inorder_bintree(bintree_t node);
void postorder_bintree(bintree_t node);

#endif