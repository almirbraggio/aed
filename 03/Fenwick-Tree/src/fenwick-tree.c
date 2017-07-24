// Author: Almir Braggio

#include "fenwick-tree.h"

// init
fwtree_t init_fwtree (void) {
	return NULL;
}

// make node
fwtree_t make_fwtree (fwtree_t parent, long int index, unsigned long int data) {
	fwtree_t node = (fwtree_t)malloc(sizeof(struct fwtree_node_t));
	node->index = index;
	node->data = data;
	node->height = 1;

	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// free
fwtree_t free_fwtree (fwtree_t node) {
	if (!isempty_fwtree(node)) {
		free_fwtree(node->left);
		free_fwtree(node->right);
		free(node);
	}
	return NULL;
}

// insert content
fwtree_t insert_fwtree (fwtree_t root, long int index, unsigned long int data) {
	fwtree_t current = root;

	if (isempty_fwtree(current)) {
		current = make_fwtree(NULL, index, data);
		return current;
	}

	while (current->index != index) {
		// to left
		if (index < current->index) {
			if (current->left) {
				current = current->left;
			}
			else {
				current->left = make_fwtree(current, index, data);
				current = current->left;
			}
		}
		// to right
		else if (index > current->index) {
			if (current->right) {
				current = current->right;
			}
			else {
				current->right = make_fwtree(current, index, data);
				current = current->right;
			}
		}
		// duplicate
		else return root;
	}
	
	// adjustment
	do {
		current  = current->parent;
		adj_height_fwtree(current);
		current = balance_fwtree(current);
	} while (current->parent);
	
	return current;
}

// balance
fwtree_t balance_fwtree (fwtree_t root) {
	if ((height_fwtree(root->left) - height_fwtree(root->right)) > 1) {
		if (height_fwtree(root->left->left) > height_fwtree(root->left->right)) {
			// simple rotate to right
			root = rotate_right_fwtree(root);
		}
		else {
			// double rotate left-right
			rotate_left_fwtree(root->left);
			root = rotate_right_fwtree(root);
		}
	}
	else if ((height_fwtree(root->right) - height_fwtree(root->left)) > 1) {
		if (height_fwtree(root->right->right) > height_fwtree(root->right->left)) {
			// simple rotate to left
			root = rotate_left_fwtree(root);
		}
		else {
			// double rotate right-left
			rotate_right_fwtree(root->right);
			root = rotate_left_fwtree(root);
		}
	}
	return root;
}

// rotate to right
fwtree_t rotate_right_fwtree (fwtree_t root) {
	fwtree_t new_root = root->left;
	if (root->parent) {
		if (root->parent->left == root)
			root->parent->left = new_root;
		else 
			root->parent->right = new_root;
	}
	
	new_root->parent = root->parent;
	root->parent = new_root;
	root->left = new_root->right;
	
	if (root->left) 
		root->left->parent = root;
	
	new_root->right = root;

	// fix height
	adj_height_fwtree(root);
	adj_height_fwtree(new_root);

	// fix sum
	fixdata_right_fwtree(new_root);

	return new_root;
}

// rotate to left
fwtree_t rotate_left_fwtree (fwtree_t root) {
	fwtree_t new_root = root->right;
	if (root->parent) {
		if (root->parent->right == root) 
			root->parent->right = new_root;
		else 
			root->parent->left = new_root;
	}
	
	new_root->parent = root->parent;
	root->parent = new_root;
	root->right = new_root->left;
	
	if (root->right)
		root->right->parent = root;
	
	new_root->left = root;

	// fix height
	adj_height_fwtree(root);
	adj_height_fwtree(new_root);

	// fix sum
	fixdata_left_fwtree(new_root);

	return new_root;
}

// adjust sum
void fixdata_right_fwtree (fwtree_t root) {
	root->data += root->right->data;
	return;
}

void fixdata_left_fwtree (fwtree_t root) {
	root->data += root->left->data;
	return;
}

// max
unsigned char max_fwtree(unsigned char a, unsigned char b) {
	return (a > b ? a : b);
}

// get height
unsigned char height_fwtree (fwtree_t root) {
	return root ? root->height : 0;
}

// adjust height
void adj_height_fwtree (fwtree_t root) {
	root->height = (unsigned char)(1 + max_fwtree(height_fwtree(root->left), \
	height_fwtree(root->right)));
}

// is empty
bool_t isempty_fwtree (fwtree_t node) {
	if (node == NULL)
		return true;
	return false;
}

// is leaf
bool_t isleaf_fwtree (fwtree_t node) {
	if ((node->left == NULL) && (node->right == NULL))
		return true;
	return false;
}

// min, max
long int min_index_tree (fwtree_t node) {
	fwtree_t r = node;
	while (r->left != NULL)
		r =  r->left;
	return r->index;
}

long int max_index_fwtree (fwtree_t node) {
	fwtree_t r = node;
	while (r->right != NULL)
		r =  r->right;
	return r->index;
}

// get prefix sum
unsigned long int sum_to_fwtree (fwtree_t node, long int to) {
	if (node == NULL)
		return 0;
	if (to < node->index)
		return sum_to_fwtree (node->left, to);
	else if (to > node->index)
		return (node->data + sum_to_fwtree (node->right, to));
	return node->data;
}

// get interval sum
unsigned long int sum_from_to_fwtree (fwtree_t node, long int from, long int to) {
	return (sum_to_fwtree (node, min_index_tree(node)) + sum_to_fwtree (node, to) - sum_to_fwtree (node, from)); 
}

// get prefix diff
unsigned long int diff_to_fwtree (fwtree_t node, long int to) {
	return (sum_to_fwtree (node, to) - sum_to_fwtree (node, min_index_tree(node)));
}

// get interval diff
unsigned long int diff_from_to_fwtree (fwtree_t node, long int from, long int to) {
	return (sum_to_fwtree (node, to) - sum_to_fwtree (node, from)); 
}

// print pre-order
void print_preorder_fwtree (fwtree_t node) {
	if (!isempty_fwtree(node)) {
#ifdef DEBUG
		printf("#%d (%d): %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
		print_preorder_fwtree(node->left);
		print_preorder_fwtree(node->right);
	}
	return;
}

// print in-order
void print_inorder_fwtree (fwtree_t node) {	
	if (!isempty_fwtree(node)) {
		print_inorder_fwtree(node->left);
#ifdef DEBUG
		printf("#%d (%d): %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
		print_inorder_fwtree(node->right);
	}
	return;
}

// print pos-order
void print_posorder_fwtree (fwtree_t node) {
	if (!isempty_fwtree(node)) {
		print_posorder_fwtree(node->left);
		print_posorder_fwtree(node->right);
#ifdef DEBUG
		printf("#%d (%d): %d\n", node->index, (int)node->height, (int)node->data);
#else
		printf("%d ", (int)node->data);
#endif
	}
	return;
}