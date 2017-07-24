// Author: Almir Braggio

#ifndef FENWICK_TREE_H_INCLUDED
#define FENWICK_TREE_H_INCLUDED

#include "avl-tree.h"

// memcpy
#include <string.h>

typedef avltree_t fwtree_t;

// init
fwtree_t init_fwtree (int input[], int size);

// free
fwtree_t free_fwtree (fwtree_t node);

// get sum
unsigned int get_sum_to_fwtree (fwtree_t node, int to);
unsigned int get_sum_from_to_fwtree (fwtree_t node, int from, int to);

// get diff
unsigned int get_diff_from_to_fwtree (fwtree_t node, int from, int to);

// find
fwtree_t find_index_fwtree (fwtree_t node, int index);

// prints
void print_preorder_fwtree (fwtree_t node);
void print_inorder_fwtree (fwtree_t node);
void print_posorder_fwtree (fwtree_t node);

int min_index_tree (fwtree_t node);
int max_index_fwtree (fwtree_t node);

#endif