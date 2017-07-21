// Author: Almir Braggio
// jun. 2017

#include "src/btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define isempty(x) 	isempty_btree(x)

// use for check seg faults and memory leaks
// valgrind --leak-check=full ./bin_tree

//void print_bintree(bintree_t r);

// Main code
int main(int argc, char *argv[]) {
	btree_t *root = init_btree();

	if (isempty(root) == true)
		printf("B-Tree is empty.\r\n");

	insert_btree(&root, 6);
	insert_btree(&root, 1);
	insert_btree(&root, 4);
	insert_btree(&root, 3);
	insert_btree(&root, 2);
	insert_btree(&root, 5);

	if (isempty(root) == false)
		printf("B-Tree is not empty.\r\n");

	inorder_btree(root);

	/*unsigned int i = 0, aux = 0;
	bintree_t tree = init_bintree();

	// Argument validation	
	if ((argc >> 1) == 0) {
		printf("Invalid arguments.\r\nYou must specify at least one argument.\r\n");
		return 0;
	}

	// One argument, then insert random data
	if ((argc >> 1) == 1) {
		aux = (unsigned int)atoi(argv[1]);
		srand((unsigned)time(NULL));
		for(i = 0; i < aux; i++) {
			unsigned int x = (unsigned int)(rand() % aux);
			tree = insert_bintree(tree, x);
		}
	}
	// More arguments, then insert values
	else {
		for(i = 1; i < argc; i++) {
			unsigned int x = (unsigned int)(atoi(argv[i]));
			tree = insert_bintree(tree, (data_t)x);
		}
	}

	// Print tree (pre, in, post order)
	print_bintree(tree);

	// Delete tree
	tree = free_bintree(tree);

	if (isempty_bintree(tree)) {
		printf("Tree is empty!\r\n");
	}
*/
	printf("Exiting!\r\n");
	return 0;
}

/*
// Prints
void print_bintree(bintree_t r) {
	// pre
	printf("Pre Order:\r\n");
	preorder_bintree(r);
	printf("\r\n");
	// in
	printf("In Order:\r\n");
	inorder_bintree(r);
	printf("\r\n");
	// post
	printf("Post Order:\r\n");
	postorder_bintree(r);
	printf("\r\n");
	return;
}
*/