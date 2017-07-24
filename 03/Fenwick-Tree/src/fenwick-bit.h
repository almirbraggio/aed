// Autor: Almir Braggio

#ifndef FENWICK_BIT_H_INCLUDED
#define FENWICK_BIT_H_INCLUDED

// init
void init_fwbit (int input[], int size);

// increment
void inc_fwbit (int input[], int size, int pos, int inc);

// set and get
void set_fwbit (int input[], int size, int pos, int value);
int get_fwbit (int input[], int size, int pos);

// sum k elements
int sum_fwbit (int input[], int size, int k);

// close fenwick
void close_fwbit (int input[], int size);

#endif