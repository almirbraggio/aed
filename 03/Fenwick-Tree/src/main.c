// Author: Almir Braggio

#include "fenwick-tree.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#define MAX		15

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
	int i = 0;
	
	int size = MAX;
	int *input = (int *)calloc(size, sizeof(int));

	fwtree_t tree = NULL;

	// reset srand
	srand((unsigned)time(NULL));

	printf("Fenwick Tree");

	println("Input data: ");
	// fill array with random data
	for (i = 0; i < size; i++) {
		input[i] = rand() % size;
		printf("%d ", input[i]);
	}

	// init fenwick tree
	tree = init_fwtree(input, size);

	// prints
	/*println("Pre-Order: ");
	print_preorder_fwtree(tree);

	println("In-Order: ");
	print_inorder_fwtree(tree);

	println("Pos-Order: ");
	print_posorder_fwtree(tree);*/

	println("Prefix Sum: ");
	for (i = 0; i < size; i++)
		printf("%d ", get_sum_to_fwtree(tree, i));
	
	println("Interval Sum: ");
	for (i = 0; i < size; i++)
		printf("%d ", get_sum_from_to_fwtree(tree, 0, i));

	println("Interval Diff: ");
	for (i = 0; i < size; i++)
		printf("%d ", get_diff_from_to_fwtree(tree, i-1, i));

	// freeee
	free(input);
	free(tree);
	
	println("Exiting!\r\n");
	return 0;
}