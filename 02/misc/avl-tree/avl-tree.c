// Author: Almir Braggio

#include "avl-tree.h"

#include <stdlib.h>
#include <stdio.h>

//#define DEBUG

// init
avltree_t init_avltree (void) { //int index, unsigned int data) {
	return NULL; //make_avltree(NULL, index, data);
}

// make node
avltree_t make_avltree (avltree_t parent, int index, unsigned int data) {
	avltree_t node = (avltree_t)malloc(sizeof(struct avltree_node_t));
	node->index = index;
	node->data = data;
	node->height = 1;

	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// insert content
avltree_t insert_avltree (avltree_t root, int index, unsigned int data) {
	avltree_t current = root;

	if (current == NULL) {
		current = make_avltree(NULL, index, data);
		return current;
	}

	while (current->index != index) {
		// to left
		if (index < current->index) {
			if (current->left) {
				current = current->left;
			}
			else {
				current->left = make_avltree(current, index, data);
				current = current->left;
			}
		}
		// to right
		else if (index > current->index) {
			if (current->right) {
				current = current->right;
			}
			else {
				current->right = make_avltree(current, index, data);
				current = current->right;
			}
		}
		// duplicate
		else return root;
	}
	
	// adjustment
	do {
		current  = current->parent;
		adj_height_avltree(current);
		current = balance_avltree(current);
	} while (current->parent);
	
	return current;
}

// to height
unsigned char max_avltree(unsigned char a, unsigned char b) {
	return (a > b ? a : b);
}

unsigned char height_avltree (avltree_t root) {
	return root ? root->height : 0;
}

void adj_height_avltree (avltree_t root) {
	root->height = (unsigned char)(1 + max_avltree(height_avltree(root->left), \
	height_avltree(root->right)));
}

// balance
avltree_t balance_avltree (avltree_t root) {
	if ((height_avltree(root->left) - height_avltree(root->right)) > 1) {
		if (height_avltree(root->left->left) > height_avltree(root->left->right)) {
			// simple rotate to right
			root = rotate_right_avltree(root);
		}
		else {
			// double rotate left-right
			rotate_left_avltree(root->left);
			root = rotate_right_avltree(root);
		}
	}
	else if ((height_avltree(root->right) - height_avltree(root->left)) > 1) {
		if (height_avltree(root->right->right) > height_avltree(root->right->left)) {
			// simple rotate to left
			root = rotate_left_avltree(root);
		}
		else {
			// double rotate right-left
			rotate_right_avltree(root->right);
			root = rotate_left_avltree(root);
		}
	}
	return root;
}

// rotate to right
avltree_t rotate_right_avltree (avltree_t root) {
	avltree_t new_root = root->left;
	if (root->parent) {
		if (root->parent->left == root)
			root->parent->left = new_root;
		else 
			root->parent->right = new_root;
	}
	
	new_root->parent = root->parent;
	root->parent = new_root;
	root->left = new_root->right;
	
	if (root->left) 
		root->left->parent = root;
	
	new_root->right = root;

	// fix height
	adj_height_avltree(root);
	adj_height_avltree(new_root);
	return new_root;
}

// rotate to left
avltree_t rotate_left_avltree (avltree_t root) {
	avltree_t new_root = root->right;
	if (root->parent) {
		if (root->parent->right == root) 
			root->parent->right = new_root;
		else 
			root->parent->left = new_root;
	}
	
	new_root->parent = root->parent;
	root->parent = new_root;
	root->right = new_root->left;
	
	if (root->right)
		root->right->parent = root;
	
	new_root->left = root;

	// fix height
	adj_height_avltree(root);
	adj_height_avltree(new_root);
	return new_root;
}

void print_preorder_avltree (avltree_t node) {	
	if (!node) {
		// is empty
		return;
	}		
	else {
#ifdef DEBUG
		printf("Index: %d; Height: %d; Data: %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
		print_preorder_avltree(node->left);
		print_preorder_avltree(node->right);
		return;
	}
}

void print_inorder_avltree (avltree_t node) {	
	if (!node) {
		// is empty
		return;
	}		
	else {
		print_inorder_avltree(node->left);
#ifdef DEBUG
		printf("Index: %d; Height: %d; Data: %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
		print_inorder_avltree(node->right);
		return;
	}
}

void print_posorder_avltree (avltree_t node) {
	if (!node) {
		// is empty
		return;
	}		
	else {
		print_posorder_avltree(node->left);
		print_posorder_avltree(node->right);
#ifdef DEBUG
		printf("Index: %d; Height: %d; Data: %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
		return;
	}
}

// find
avltree_t find_index_avltree (avltree_t node, int index) {
	if (node == NULL)
		return NULL;
	if (index < node->index)
		return find_index_avltree(node->left, index);
	else if (index > node->index)
		return find_index_avltree(node->right, index);
	else
		return node;
}