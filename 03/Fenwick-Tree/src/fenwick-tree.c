// Author: Almir Braggio

#include "fenwick-tree.h"

// init
bintree_t init_bintree (void) {
	bintree_t tree = NULL;
	return tree;
}

// free
bintree_t free_bintree (bintree_t node) {
	if (isempty_bintree(node))
		return NULL;
	free_bintree(node->left);
	free_bintree(node->right);
	
	free(node);
	return NULL;
}

// empty
bool_t isempty_bintree (bintree_t node) {
	return (bool_t)(node == NULL);
}

// insert
bintree_t insert_bintree (bintree_t node, data_t data) {
	if (isempty_bintree(node)) {
		node = (struct bintree_node_t *)malloc(sizeof(struct bintree_node_t));
		node->data = data;
		node->left = node->right = NULL; 
	}
	else {
		if (data < node->data)
			node->left = insert_bintree(node->left, data);
		else if (data > node->data)
			node->right = insert_bintree(node->right, data);
	}
	return node;
}

// search
data_t min_bintree (bintree_t node) {
	bintree_t r = node;
	while (r->left != NULL)
		r =  r->left;
	return r->data;
}

data_t max_bintree (bintree_t node) {
	bintree_t r = node;
	while (r->right != NULL)
		r =  r->right;
	return r->data;
}

// prints
void preorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		printf("%d ", node->data);
		preorder_bintree(node->left);
		preorder_bintree(node->right);
	}
	return;
}

void inorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		inorder_bintree(node->left);
		printf("%d ", node->data);
		inorder_bintree(node->right);
	}
	return;
}

void postorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		postorder_bintree(node->left);
		postorder_bintree(node->right);
		printf("%d ", node->data);
	}
	return;
}