// Author: Almir Braggio

#include "fenwick-tree.h"
#include "fenwick-bit.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#define MAX		7

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

	//int arr[7] = {5, 1, 15, 11, 52, 28, 0};

	input[0] = 0;//5;
	input[1] = 28;//1;
	input[2] = 52;//15;
	input[3] = 11;
	input[4] = 15;//52;
	input[5] = 1;//28;
	input[6] = 5;//0;
	init_fwbit(input, 7);

	for (i = 0; i < 7; i++)
		printf("%d ", input[i]);

	//return 0;

	// init fenwick tree
	printf("Initializing Fenwick Tree...");
	fwtree_t tree = init_fwtree();

	/*// reset srand
	srand((unsigned)time(NULL));

	println("Input data: ");
	// fill array with random data
	for (i = 0; i < size; i++) {
		input[i] = rand() % size;
		printf("%d ", input[i]);
	}*/

	//for (i = 1; i < 8; i++)
	//	tree = insert_fwtree(tree, i, arr[i-1]);
	
	tree = insert_fwtree(tree, 0, 0);
	tree = insert_fwtree(tree, 1, 28);
	tree = insert_fwtree(tree, 2, 52);
	tree = insert_fwtree(tree, 3, 11);
	tree = insert_fwtree(tree, 4, 15);
	tree = insert_fwtree(tree, 5, 1);
	tree = insert_fwtree(tree, 6, 5);	

	// print
	println("\r\n");
	print_inorder_fwtree(tree);

	println("Prefix Sum: ");
	for (i = 0; i < size; i++)
		printf("%d ", sum_to_fwtree(tree, i));
	
	println("Interval Sum: ");
	for (i = 0; i < size; i++)
		printf("%d ", sum_from_to_fwtree(tree, 0, i));

	println("Interval Diff: ");
	for (i = 0; i < size; i++)
		printf("%d ", diff_from_to_fwtree(tree, i-1, i));

	// freeee
	free(input);
	
	tree = free_fwtree(tree);
	if (isempty_fwtree(tree))
		println("Freeee!");
	
	println("Exiting!\r\n");
	return 0;
}