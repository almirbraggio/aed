// Author: Almir Braggio

#include "fenwick-tree.h"

// init
fwtree_t init_fwtree (int input[], int size) {
	fwtree_t root = init_avltree();
	int *arr = (int *)calloc(size, sizeof(int));
	int i = 0, j = 0;
	
	// copy array
	memcpy(arr, input, (sizeof(int)*size));

	if (size) {
		// create the input array into a fenwick tree
		for (i = 0; i < size; i++) {
			for (j = 1; (i & j) == j; j <<= 1) {
				arr[i] += arr[i-j];
			}
		}
		// insert on tree
		for (i = 0; i < size; i++) {
			root = insert_avltree(root, i, arr[i]);
		}
	}

	// freeee
	free(arr);
	return root;
}

// free
fwtree_t free_fwtree (fwtree_t node) {
	if (node == NULL)
		return NULL;
	
	free_fwtree(node->left);
	free_fwtree(node->right);
	
	free(node);
	return NULL;
}

// get prefix sum
unsigned int get_sum_to_fwtree (fwtree_t node, int to) {
	if (node == NULL)
		return 0;
	if (to < node->index)
		return get_sum_to_fwtree (node->left, to);
	else if (to > node->index)
		return (node->data + get_sum_to_fwtree (node->right, to));
	return node->data;
}

// get interval sum
unsigned int get_sum_from_to_fwtree (fwtree_t node, int from, int to) {
	return (get_sum_to_fwtree (node, 0) + get_sum_to_fwtree (node, to) - get_sum_to_fwtree (node, from)); 
}

// get interval diff
unsigned int get_diff_from_to_fwtree (fwtree_t node, int from, int to) {
	return (get_sum_to_fwtree (node, to) - get_sum_to_fwtree (node, from)); 
}

// find
fwtree_t find_index_fwtree (fwtree_t node, int index) {
	return find_index_avltree(node, index);
}

// prints
void print_preorder_fwtree (fwtree_t node) {
	print_preorder_avltree (node);
	return;
}

void print_inorder_fwtree (fwtree_t node) {
	print_inorder_avltree (node);
	return;
}

void print_posorder_fwtree (fwtree_t node) {
	print_posorder_avltree (node);
	return;
}

// min, max
int min_index_tree (fwtree_t node) {
	fwtree_t r = node;
	while (r->left != NULL)
		r =  r->left;
	return r->index;
}

int max_index_fwtree (fwtree_t node) {
	fwtree_t r = node;
	while (r->right != NULL)
		r =  r->right;
	return r->index;
}
