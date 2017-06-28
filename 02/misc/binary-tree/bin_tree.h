// Author: Almir Braggio
// jun. 2017

#ifndef BIN_TREE_H_INCLUDED
#define BIN_TREE_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL    (0)
#endif

typedef struct bintree_node {
    void 	*data;
    struct 	bintree_node *left, *right;
} bintree_node_t;

typedef struct bintree {
    size_t size;
    struct bintree_node *root;
} bintree_t;

bintree_t *init_bintree (size_t size);

bintree_t *free_bintree (bintree_t *tree);
bintree_node_t *free_node_bintree (bintree_node_t *node);

#endif