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

// ---

typedef struct btree_node_t {
    uint n; 						// keys in node
    uint keys[M-1]; 				// array of keys
    struct btree_node_t *p[M]; 		// pointers will be in use
} btree_t;

enum key_status {
	Success,
	Error,
	Insert,
	Duplicate,
	Less_Keys
};

// ---

// init
btree_t *init_btree (void);

// TODO: free

// insert
bool_t insert_btree (btree_t **node, uint key);
key_status_t insert_aux_btree (btree_t *ptr, uint key, uint *up_key, btree_t **new_node);

// remove
bool_t remove_btree (btree_t **node, uint key);
key_status_t remove_aux_btree (btree_t *root, btree_t *ptr, uint key);

// search
btree_t *search_btree (btree_t *node, uint key, int *pos);
bool_t search_key_btree (btree_t *node, uint key);
int search_pos_btree (uint key, uint *key_arr, uint n);

// empty or leaf
bool_t isempty_btree (btree_t *node);
bool_t isleaf_btree (btree_t *node);

// prints
void inorder_btree (btree_t *node);
void printall_btree (btree_t *node, int tabs);

// min, max and total
uint min_btree (btree_t *node);
uint max_btree (btree_t *node);
int total_btree (btree_t *node);

#endif