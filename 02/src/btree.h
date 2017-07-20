// Author: Almir Braggio
// jul. 2017

#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "util.h"

// ---

#define M 	4

typedef unsigned int uint;

typedef struct btree_node_t {
    uint n; 			// keys in node
    uint keys[M-1]; 	// array of keys
    struct btree_node_t *p[M]; 			// pointers will be in use
} btree_t;

enum key_status {
	Duplicate, 
	Search_Failure,
	Success,
	Insert_It,
	Less_Keys 
};

// ---

// init
btree_t *init_btree (void);


/*
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
*/
#endif