// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

// init binary tree
bintree_t *init_bintree (size_t size) {
    bintree_t *ptr = (bintree_t *)malloc(sizeof(bintree_t));

    if (ptr == NULL)
        exit(EXIT_FAILURE);

    ptr->size = size;
    ptr->root = NULL;

    return (bintree_t *)ptr;
}

// free binary tree from root
bintree_t *free_bintree (bintree_t *tree) {
	if (tree) {
		bintree_node_t *ptr = tree->root;
        ptr = free_node_bintree(ptr);
		free(tree);
	}
	return (bintree_t *)NULL;
}

// free binary tree from node
bintree_node_t *free_node_bintree (bintree_node_t *node) {
	if(node) {
		node->left = free_node_bintree(node->left);
		node->right = free_node_bintree(node->right);
		free(node);
	}
	return (bintree_node_t *)NULL;
}
