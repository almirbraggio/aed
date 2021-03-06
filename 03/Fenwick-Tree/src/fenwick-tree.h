// Author: Almir Braggio

#ifndef FENWICK_TREE_H_INCLUDED
#define FENWICK_TREE_H_INCLUDED

#include <stdio.h> 		// print
#include <stdlib.h>		// free
#include <string.h>		// memcpy

//#define DEBUG

#define null    	(0)
#define bool_t 		unsigned char
#define true		1
#define false		0

typedef struct fwtree_node_t *fwtree_t;

struct fwtree_node_t {
	long int index;
	unsigned long int data;
	unsigned char height;
	fwtree_t left, right, parent;
};


// init and make
fwtree_t init_fwtree (void);
fwtree_t make_fwtree (fwtree_t parent, long int index, unsigned long int data);

// free
fwtree_t free_fwtree (fwtree_t node);

// insert
fwtree_t insert_fwtree (fwtree_t root, long int index, unsigned long int data);
fwtree_t balance_fwtree (fwtree_t root);

// rotate
fwtree_t rotate_right_fwtree (fwtree_t root);
fwtree_t rotate_left_fwtree (fwtree_t root);

// fix sum
void fixdata_right_fwtree (fwtree_t root);
void fixdata_left_fwtree (fwtree_t root);

// height
unsigned char max_fwtree(unsigned char a, unsigned char b);
unsigned char height_fwtree (fwtree_t root);
void adj_height_fwtree (fwtree_t root);

// aux functions
bool_t isempty_fwtree (fwtree_t node);
bool_t isleaf_fwtree (fwtree_t node);

// min, max
long int min_index_tree (fwtree_t node);
long int max_index_fwtree (fwtree_t node);

// find
fwtree_t find_index_fwtree (fwtree_t node, long int index);

// sum
unsigned long int sum_to_fwtree (fwtree_t node, long int to);
unsigned long int sum_from_to_fwtree (fwtree_t node, long int from, long int to);

// diff
unsigned long int diff_to_fwtree (fwtree_t node, long int to);
unsigned long int diff_from_to_fwtree (fwtree_t node, long int from, long int to);

// prints
void print_preorder_fwtree (fwtree_t node);
void print_inorder_fwtree (fwtree_t node);
void print_posorder_fwtree (fwtree_t node);

#endif