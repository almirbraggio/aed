// Author: Almir Braggio
// jun. 2017

#include "bin_tree.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i = 0, tam = atoi(argv[1]);
    bintree_t *tree = init_bintree(sizeof(int));

    printf("Binary Tree created!\r\n");
    printf("- size: %d bytes\r\n", (int)tree->size);

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
