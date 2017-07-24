// Autor: Almir Braggio

#ifndef FENWICK_ARR_H_INCLUDED
#define FENWICK_ARR_H_INCLUDED

// init
void init_fwarr (int input[], int size);

// increment
void inc_fwarr (int input[], int size, int pos, int inc);

// set and get
void set_fwarr (int input[], int size, int pos, int value);
int get_fwarr (int input[], int size, int pos);

// sum k elements
int sum_fwarr (int input[], int size, int k);

// close fenwick
void close_fwarr (int input[], int size);

#endif