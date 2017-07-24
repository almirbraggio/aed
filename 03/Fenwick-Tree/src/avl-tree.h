// Author: Almir Braggio

#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL    (0)
#endif

typedef struct avltree_node_t *avltree_t;

struct avltree_node_t {
	int index;
	unsigned int data;
	unsigned char height;
	avltree_t left, right, parent;
};

// init and make
avltree_t init_avltree (void); //int index, unsigned int data);
avltree_t make_avltree (avltree_t parent, int index, unsigned int data);

// insert
avltree_t insert_avltree (avltree_t root, int index, unsigned int data);

// height
unsigned char max_avltree(unsigned char a, unsigned char b);
unsigned char height_avltree (avltree_t root);
void adj_height_avltree (avltree_t root);

// balance
avltree_t balance_avltree (avltree_t root);

// rotate
avltree_t rotate_right_avltree (avltree_t root);
avltree_t rotate_left_avltree (avltree_t root);

// prints
void print_preorder_avltree (avltree_t node);
void print_inorder_avltree (avltree_t node);
void print_posorder_avltree (avltree_t node);

// find
avltree_t find_index_avltree (avltree_t node, int index);

#endif