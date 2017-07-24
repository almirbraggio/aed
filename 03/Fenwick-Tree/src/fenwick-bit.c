// Author: Almir Braggio

#include "fenwick-bit.h"

// create the input array into a fenwick tree
void init_fwbit (int input[], int size) {
	int i = 0, j = 0;
	for (i = 0; i < size; ++i) {
		for (j = 1; (i & j) == j; j <<= 1) {
			input[i] += input[i - j];
		}
	}
}

// increment the element pos by inc
void inc_fwbit (int input[], int size, int pos, int inc) {
	int i;
	
	// validation
	if (pos > size)
		return;

	input[pos] += inc;
	for (i = 1; (pos + i) < size; i <<= 1) {
		if ((pos & i) == 0) {
			pos += i;
			input[pos] += inc;
		}
	}
}

// set the element pos to value
void set_fwbit(int input[], int size, int pos, int value) {
	inc_fwbit (input, size, pos, value - get_fwbit(input, size, pos));
}

// get the element pos
int get_fwbit (int input[], int size, int pos) {
	int i = 0;
	int aux = 0;
	
	// validation
	if (pos > size)
		return 0;

	aux = input[pos];
	for (i = 1; (pos & i) == i; i <<= 1)
		aux -= input[pos-i];
	return aux;
}

// sum the first k elements
int sum_fwbit (int input[], int size, int k) {
	int i = 0;
	int total = 0;
	
	// validation
	if (k > size)
		return 0;

	for (i = 1; i <= k; i <<= 1) {
		if ((k & i) == 0)
			k += i;
		else
			total += input[k - i];
	}
	return total;
}

// revert to original array
void close_fwbit (int input[], int size) {
	int i = 0, j = 0;
	for (i = (size - 1); i >= 0; --i) {
		for (j = 1; (i & j) == j; j <<= 1) {
			input[i] -= input[i - j];
		}
	}
}