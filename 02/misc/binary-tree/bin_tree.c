// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

// init
bintree_t *init_bintree (void) {
	bintree_t *tree = (bintree_t *)malloc(sizeof(bintree_t));
	tree->root = NULL;
	return tree;
}

bintree_node_t *init_node_bintree (void) {
	bintree_node_t *node = (bintree_node_t *)malloc(sizeof(bintree_node_t));
	node->left = node->right = NULL;
	return node;
}

// free
void free_bintree (bintree_t *tree) {
	if (tree == NULL)
		return;
	free_node_bintree(tree->root);
	free(tree);
	return;
}

void free_node_bintree (bintree_node_t *node) {
	if (node == NULL)
		return;
	free_node_bintree(node->left);
	free_node_bintree(node->right);
	free(node);
	return;
}

// prints
void preorder_bintree(bintree_node_t *node) {
	if (node != NULL) {
		printf("%d ", node->data);
		preorder_bintree(node->left);
		preorder_bintree(node->right);
	}
	return;
}

void inorder_bintree(bintree_node_t *node) {
	if (node){
		inorder_bintree(node->left);
		printf("%d ", node->data);
		inorder_bintree(node->right);
	}
	return;
}

void postorder_bintree(bintree_node_t *node) {
	if (node){
		postorder_bintree(node->left);
		postorder_bintree(node->right);
		printf("%d ", node->data);
	}
	return;
}