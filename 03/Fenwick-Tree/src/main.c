// Author: Almir Braggio

#include "fenwick-tree.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

//#define PRINT

// use for check seg faults and memory leaks
// valgrind --leak-check=full ./bin_tree

static void println (const char *fmt, ...) {
	va_list argp;
	
	fputc('\n', stdout);

	va_start(argp, fmt);
	vfprintf(stdout, fmt, argp);
	va_end(argp);
	return;
}

// Main code
int main (int argc, char *argv[]) {
	long int i = 0, j = 0;
	
	// Argument validation	
	if ((argc >> 1) == 0) {
		printf("Invalid arguments.\r\nYou must specify one argument.\r\n");
		return 0;
	}

	long int size = atoi(argv[1]);
	unsigned long int *input = (unsigned long int *)calloc(size, sizeof(unsigned long int));
	long int ta = 0, tb = 0;
	long int to = 0, sum = 0;

	// init fenwick tree
#ifdef PRINT	
	printf("Initializing Fenwick Tree...");
#endif
	fwtree_t tree = init_fwtree();
	
	// reset srand
	srand((unsigned)time(NULL));

#ifdef PRINT
	println("Input data: \t");
#endif
	// fill array with random data
	ta = clock();
	for (i = 0; i < size; i++) {
		input[i] = rand() % size;
#ifdef PRINT
		printf("%d ", input[i]);
#endif
	}
	ta = (clock() - ta);

	tb = clock();
	// generate fenwick tree
	for (i = 0; i < size; i++) {
		tree = insert_fwtree(tree, i, input[i]);
	}
	tb = (clock() - tb);


	println("%*s\t%*s\t%*s", 12, "t1", 12, "t2", 12, "t1/t2");
	println("%*.lf\t%*.lf\t%*.4lf\r\n", 12, (double)ta, 12, (double)tb, 12, (double)ta/(double)tb);

	// print tree
#ifdef PRINT
	println("Fenwick Tree: \t");
	print_inorder_fwtree(tree);
#endif	

	println("%*s\t%*s\t%*s\t%*s\t%*s\t%*s", 16, "index", 16, "array", 16, "tree", 8, "t1", 8, "t2", 16, "t1/t2");
	for(i = 0; i < 10; i++) {
		
		to = (size / 10) * i;
		println("%*ld\t", 16, to);
		
		ta = clock();
		sum = 0;
		for (j = 0; j <= to; j++)
			sum = sum + input[j];
		printf("%*ld\t", 16, sum);
		ta = (clock() - ta);

		tb = clock();
		printf("%*ld\t", 16, sum_from_to_fwtree(tree, 0, to));
		tb = (clock() - tb);

		printf("%*.lf\t%*.lf\t%*.4lf", 8, (double)ta, 8, (double)tb, 16, (double)ta/(double)tb);
	}
	println("\r\n");

	// freeee
	free(input);
	
	tree = free_fwtree(tree);
#ifdef PRINT
	if (isempty_fwtree(tree))
		println("Freeee!");
	println("Exiting!\r\n");
#endif
	return 0;
}