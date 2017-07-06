// Author: Almir Braggio
// jun. 2017

#ifndef BIN_TREE_H_INCLUDED
#define BIN_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

#define UNUSED(x) (void)(x)

typedef unsigned int data_t;

typedef struct bintree_node {
	data_t data;
	struct bintree_node *left, *right;
} bintree_node_t;

typedef struct bintree {
	struct bintree_node *root;
} bintree_t;

// init
bintree_t *init_bintree (void);
bintree_node_t *init_node_bintree (void);

// free
void free_bintree (bintree_t *tree);
void free_node_bintree (bintree_node_t *node);

// prints
void preorder_bintree(bintree_node_t *node);
void inorder_bintree(bintree_node_t *node);
void postorder_bintree(bintree_node_t *node);

#endif