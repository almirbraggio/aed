// Author: Almir Braggio

#include "src/avl-tree.h"
#include "src/fenwick-bit.h"

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
	int *in1 = (int *)calloc(MAX, sizeof(int));

	avltree_t avl = init_avltree(1, 1);

	for (i = 2; i <= 7; i++) {
		avl = insert_avltree(avl, i, i);
	}
	print_inorder_avltree(avl);



	/*

	// reset srand
	//srand((unsigned)time(NULL));

	printf("Fenwick Tree");

	println("Input data: ");
	// fill array with random data
	for (i = 0; i < MAX; i++) {
		in1[i] = rand() % MAX;
		printf("%d ", in1[i]);
	}

	init_fwbit(in1, MAX);

	println("Fenwick bit: ");
	for (i = 0; i < MAX; i++) {
		printf("%d ", in1[i]);
	}

	// freeee
	free(in1);*/
	
	println("Exiting!\r\n");
	return 0;
}