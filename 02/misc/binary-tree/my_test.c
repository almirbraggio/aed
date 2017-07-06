// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef NULL
#define NULL	(0)
#endif

void print_bintree(bintree_t *tree);

// Main code
int main(int argc, char *argv[]) {
	unsigned int i = 0, aux = 0;
	bintree_t *tree = init_bintree();

	// Argument validation	
	if ((argc >> 1) == 0) {
		printf("Invalid arguments.\r\nYou must specify at least one argument.\r\n");
		return 0;
	}

	// One argument, then insert random data
	/*if ((argc >> 1) == 1) {
		aux = (unsigned int)atoi(argv[1]);
		srand((unsigned)time(NULL));
		for(i = 0; i < aux; i++) {
			unsigned int x = (unsigned int)(rand() % aux);
			tree->root = insert_bintree(tree, x);
		}
	}
	// More arguments, then insert values
	else {
		root = init_bintree((data_t)atoi(argv[1]));
		for(i = 2; i < argc; i++) {
			unsigned int x = (unsigned int)(atoi(argv[i]));
			root = insert_bintree(root, (data_t)x);
		}
	}*/

	// Print tree (pre, in, post order)
	print_bintree(tree);

	// Delete tree
	free_bintree(tree);
	if (tree->root == NULL) {
		printf("Tree deleted!\r\n");
	}

	printf("Exiting!\r\n");
	return 0;
}

void print_bintree(bintree_t *tree) {
	printf("Pre Order:\r\n");
	preorder_bintree(tree->root);
	printf("\r\n");

	printf("In Order:\r\n");
	inorder_bintree(tree->root);
	printf("\r\n");

	printf("Post Order:\r\n");
	postorder_bintree(tree->root);
	printf("\r\n");

	return;
}