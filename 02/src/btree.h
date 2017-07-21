// Author: Almir Braggio
// jul. 2017

#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "useful.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---

#define M 	3

typedef unsigned int uint;
typedef enum key_status key_status_t;

typedef struct btree_node_t {
    uint n; 						// keys in node
    uint keys[M-1]; 				// array of keys
    struct btree_node_t *p[M]; 		// pointers will be in use
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

// insert
bool_t insert_btree (btree_t **node, uint key);

// status
key_status_t status_btree (btree_t *ptr, uint key, uint *up_key, btree_t **new_node);

// search
bool_t search_btree (btree_t *node, uint key);

// search position
int search_pos_btree (uint key, uint *key_arr, uint n);

// empty
bool_t isempty_btree (btree_t *node);

// print in sorted order
void inorder_btree (btree_t *node);

// total keys
int total_btree (btree_t *node);

// min and max key
uint min_btree (btree_t *node);
uint max_btree (btree_t *node);



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