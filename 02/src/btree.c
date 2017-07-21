// Author: Almir Braggio
// jul. 2017

#include "btree.h"

// init
btree_t *init_btree (void) {
	btree_t *root = NULL;
	return root;
}

/*
// free
bintree_t free_bintree (bintree_t node) {
	if (isempty_bintree(node))
		return NULL;
	free_bintree(node->left);
	free_bintree(node->right);
	
	free(node);
	return NULL;
}
*/

// insert
bool_t insert_btree (btree_t **node, uint key) {
	btree_t *new_node = NULL;
	uint up_key = 0;
	enum key_status status = status_btree((*node), key, &up_key, &new_node);
	// duplicate key
	if (status == Duplicate) {
		//printf("Key already available\n");
		return (bool_t)false;
	}
	// new node
	else if (status == Insert_It) {
		btree_t *up_root = (*node);
		(*node) = (struct btree_node_t *)malloc(sizeof(btree_t));
		(*node)->n = 1;
		(*node)->keys[0] = up_key;
		(*node)->p[0] = up_root;
		(*node)->p[1] = new_node;
		return (bool_t)true;
	}
	return (bool_t)false;
}

// status
key_status_t status_btree (btree_t *ptr, uint key, uint *up_key, btree_t **new_node) {
	btree_t *new_ptr = NULL, *last_ptr = NULL;
	uint new_key = 0, last_key = 0, n = 0;
	enum key_status value;

	// aux
	int pos = 0, i = 0, split = 0;
	
	// new node, insert it
	if (ptr == NULL) {
		*new_node = NULL;
		*up_key = key;
		return Insert_It;
	}

	// get keys in node
	n = ptr->n;
	// search position
	pos = search_pos_btree(key, ptr->keys, n);
	// validation
	if ((pos < n) && (key == ptr->keys[pos])) {
		return Duplicate;
	}
	// recursive status
	value = status_btree(ptr->p[pos], key, &new_key, &new_ptr);
	if (value != Insert_It) {
		return value;
	}
	
	// if keys in node is less than M-1
	// where M is order of B tree
	if (n < (M-1)) {
		// search position
		pos = search_pos_btree(new_key, ptr->keys, n);
		// shifting the key and pointer
		for (i = n; i > pos; i--) {
			ptr->keys[i] = ptr->keys[i-1];
			ptr->p[i+1] = ptr->p[i];
		}
		// key is inserted at exact location
		ptr->keys[pos] = new_key;
		ptr->p[pos+1] = new_ptr;
		// incrementing the number of keys in node
		++ptr->n;
		return Success;
	}

	// if keys in nodes are maximum and position of node to be inserted is last
	if (pos == (M-1)) {
		last_key = new_key;
		last_ptr = new_ptr;
	}
	// or is not last
	else {
		last_key = ptr->keys[M-2];
		last_ptr = ptr->p[M-1];
		// shifting the key and pointer
		for (i = (M-2); i > pos; i--) {
			ptr->keys[i] = ptr->keys[i-1];
			ptr->p[i+1] = ptr->p[i];
		}
		// key is inserted
		ptr->keys[pos] = new_key;
		ptr->p[pos+1] = new_ptr;
	}

	// split calc
	split = (M-1)/2;
	(*up_key) = ptr->keys[split];
	// new node after split
	(*new_node)= (struct btree_node_t *)malloc(sizeof(btree_t));
	// keys for left splitted node
	ptr->n = split;
	// keys for right splitted node
	(*new_node)->n = M-1-split;
	for (i=0; i < (*new_node)->n; i++) {
		(*new_node)->p[i] = ptr->p[i+split+1];
		if (i < (((*new_node)->n)-1))
			(*new_node)->keys[i] = ptr->keys[i+split+1];
		else
			(*new_node)->keys[i] = last_key;
	}
	(*new_node)->p[(*new_node)->n] = last_ptr;
	return Insert_It;
}

// search
bool_t search_btree (btree_t *node, uint key) {
	uint n = 0;
	int pos = 0;
	btree_t *ptr = node;
	while (ptr) {
		n = ptr->n;
		pos = search_pos_btree(key, ptr->keys, n);
		if (pos < n && key == ptr->keys[pos]) {
			return true;
		}
		ptr = ptr->p[pos];
	}
	return false;
}

// search position
int search_pos_btree (uint key, uint *key_arr, uint n) {
	int pos = 0;
	while ((pos < n) && (key > key_arr[pos])) {
		pos++;
	}
	return pos;
}

// empty
bool_t isempty_btree (btree_t *node) {
	return (bool_t)(node == NULL);
}

// print in sorted order
void inorder_btree (btree_t *node) {
	if (!isempty_btree(node)) {
		if ((node->n) >= 1) {
			inorder_btree(node->p[0]);
			printf("%d ", (int)(node->keys[0]));
			inorder_btree(node->p[1]);
			if ((node->n) == 2) {
				printf("%d ", (int)(node->keys[1]));
				inorder_btree(node->p[2]);
			}
		}
	}
	return;
}

// total keys
int total_btree (btree_t *node) {
	int count = 0, i = 0;
	if (!isempty_btree(node)) {
		count = 1;
		if ((node->n) >= 1) {
			for (i = 0; i < ((M/2)+1); i++) {
				count += total_btree(node->p[i]);
			}
			if ((node->n) == 2) {
				count += total_btree(node->p[2]) + 1;
			}
		}
	}
	return count;
}

// min key
uint min_btree (btree_t *node) {
	uint min = 0;
	if (!isempty_btree(node)) {
		if (node->p[0] != NULL) {
			min = min_btree(node->p[0]);
		}
		else {
			min = node->keys[0];
		}
	}
	return min;
}

// max key
uint max_btree (btree_t *node) {
	uint max = 0;
	if (!isempty_btree(node)) {
		if ((node->n) == 1) {
			if ((node->p[1]) != NULL) {
				max = max_btree(node->p[1]);
			}
			else {
				max = node->keys[0];
			}
		}
		if ((node->n) == 2) {
			if ((node->p[2]) != NULL) {
				max = max_btree(node->p[2]);
			}
			else {
				max = node->keys[1];
			}
		}
	}
	return max;
}

/*
// finds the maximum level
int max_level_btree (btree_t *node) {
	if (node) {
		int l = 0, mr = 0, r = 0, max_depth;
		if (node->p[0] != NULL) l = maxLevel(node->p[0]);
		if (node->p[1] != NULL) mr = maxLevel(node->p[1]);	
		if (node->n == 2) {
			if (node->p[2] != NULL) r = maxLevel(node->p[2]);
		}
		max_depth = max(l, mr, r) + 1;
		return max_depth;
	}
	return 0;
}*/
