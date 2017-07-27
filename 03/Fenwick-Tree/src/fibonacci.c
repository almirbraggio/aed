// Author: Almir Braggio

#include "fenwick-tree.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#define PRINT

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
	long int i = 0;
	
	// Argument validation	
	if ((argc >> 1) == 0) {
		printf("Invalid arguments.\r\nYou must specify one argument.\r\n");
		return 0;
	}

	long int size = atoi(argv[1]);
	unsigned long int input = 0;

	if (size > 47) {
		printf("Out of range.\r\nMax 47\r\n");
		return 0;
	}

	// init fenwick tree
	fwtree_t fib = init_fwtree();

	// generate fenwick tree with fibonacci numbers
	for (i = 0; i < size; i++) {
		if (i == 0)
			input = 0;
		else if ((i == 1)||(i == 2))
			input = 1;
		else
			input = sum_to_fwtree(fib, i-1) - sum_to_fwtree(fib, i-3);
		fib = insert_fwtree(fib, i, input);
	}


	// print tree
#ifdef PRINT
	println("Fenwick Tree: \t");
	print_inorder_fwtree(fib);
#endif

#ifdef PRINT
	println("Fibonacci Seq: \t");
	for (i = 0; i < size; i++) {
		printf("%d ", (int)diff_from_to_fwtree(fib, i-1, i));
	}
#endif

	fib = free_fwtree(fib);
#ifdef PRINT
	if (isempty_fwtree(fib))
		println("Freeee!");
	println("Exiting!\r\n");
#endif
	return 0;
}