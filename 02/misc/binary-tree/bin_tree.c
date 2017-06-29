// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

#define MAX_STR		32

// init binary tree
bintree_t *init_bintree (size_t size, char *info) {
    bintree_t *ptr = (bintree_t *)malloc(sizeof(bintree_t));
    char *str = (char *)calloc(1,MAX_STR);

    if (ptr == NULL)
        exit(EXIT_FAILURE);

    if (str == NULL)
        exit(EXIT_FAILURE);

    memcpy(str, (const void *)info, MAX_STR);;

    // init tree
    ptr->size = size;
    ptr->root = NULL;
    ptr->info = str;    

    return (bintree_t *)ptr;
}

// free binary tree from root
bintree_t *free_bintree (bintree_t *tree) {
	if (tree) {
		bintree_node_t *ptr = tree->root;
        ptr = free_node_bintree(ptr);
        // free char field
        free(tree->info);
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
