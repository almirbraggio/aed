// Author: Almir Braggio
// jun. 2017

#include "src/useful.h"
#include "src/btree.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

//#define DBG
#define TEST			9

#define isempty(x) 		isempty_btree(x)

// use for check seg faults and memory leaks
// valgrind --leak-check=full ./bin_tree

static void println(const char *fmt, ...) {
	va_list argp;
	
	fputc('\n', stdout);

	va_start(argp, fmt);
	vfprintf(stdout, fmt, argp);
	va_end(argp);
	return;
}

// Main code
int main(int argc, char *argv[]) {
	btree_t *root = init_btree();
	int i = 0, aux = 0;
	bool_t status = false;

#ifdef DBG
	if (isempty(root) == true)
		println("B-Tree is empty.");
#endif

	println("Input:\t");
	srand((unsigned)time(NULL));
	for (i = 0; i < TEST; i++) {
		aux = (int)(rand() % 100);
		status = insert_btree(&root, (uint)aux);
		// TODO: verificar status true/false
		//if (status == true)
		printf("%d ", aux);
	}

#ifdef DBG
	if (isempty(root) == false)
		println("B-Tree is not empty.");
#endif

	println("Output:\t");
	inorder_btree(root);

	println("Status:");
	println("\tMin %d < Max %d", (int)min_btree(root), (int)max_btree(root));
	println("\tTotal = %d", total_btree(root));

	println("Exiting!");
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