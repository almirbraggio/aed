// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

#include <stdio.h>
#include <stdlib.h>

// Main code
int main(int argc, char *argv[]) {
	int i = 0, tam = 0;
	bintree_t *tree = NULL;

	// Argument validation	
	if ((argc >> 1) == 0) {
		printf("Invalid arguments. Missing test size input.\r\n");
		return 0;
	}

	// Init variables
	tam = atoi(argv[1]);
	tree = init_bintree(sizeof(int), "My Binary Tree");

	// Tree info
    printf("Binary Tree created!\r\n");
    printf("- size: %d bytes\r\n", (int)tree->size);
    printf("- info: %s\r\n", (char *)tree->info);

    // Delete tree
	tree = free_bintree(tree);
    if (tree == NULL) {
        printf("Binary Tree deleted!\r\n");
    }

    /*for(i = 0; i < tam; i++) {
        tree = insert_bintree(tree, (const void *)i);
    }*/

    printf("Exiting!\r\n");
    return 0;
}
