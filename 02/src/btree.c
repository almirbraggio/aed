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
	enum key_status status = insert_aux_btree((*node), key, &up_key, &new_node);
	
	// new node
	if (status == Insert) {
		btree_t *up_root = *node;
		*node = (struct btree_node_t *)malloc(sizeof(btree_t));
		(*node)->n = 1;
		(*node)->keys[0] = up_key;
		(*node)->p[0] = up_root;
		(*node)->p[1] = new_node;
		return true;
	}
	
	return false;
}

// insert aux
key_status_t insert_aux_btree (btree_t *ptr, uint key, uint *up_key, btree_t **new_node) {
	btree_t *new_ptr = NULL, *last_ptr = NULL;
	uint new_key = 0, last_key = 0, n = 0;
	key_status_t value;

	// aux
	int pos = 0, i = 0, split = 0;
	
	// new node, insert it
	if (isempty_btree(ptr)) {
		*new_node = NULL;
		*up_key = key;
		return Insert;
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
	value = insert_aux_btree(ptr->p[pos], key, &new_key, &new_ptr);
	if (value != Insert) {
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
	*up_key = ptr->keys[split];
	// new node after split
	*new_node = (struct btree_node_t *)malloc(sizeof(btree_t));
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
	return Insert;
}

// remove
bool_t remove_btree (btree_t **node, uint key) {
	enum key_status status = remove_aux_btree((*node), key);
	if (status == Less_Keys) {
		btree_t *up_root = *node;
		*node = (*node)->p[0];
		free(up_root);
		return true;
	}
	return false;
}

key_status_t remove_aux_btree (btree_t *ptr, uint key) {
	/*btree_t *left_ptr = NULL, *right_ptr = NULL;
	btree_t **p;
	key_status_t value;
	
	uint *key_arr = NULL;
	int pos, i, pivot, n;

	// minimum number of keys
	int min = (M-1)/2;
	
	// pointer null, error
	if (ptr == NULL)
		return Error;

	// assigns values of node
	n=ptr->n;
	key_arr = ptr->keys;
	p = ptr->p;
	
	// search position for key to delete
	pos = search_pos_btree(key, key_arr, n);

	// if p is a leaf
	if (p[0] == NULL) {
		if ((pos == n) || (key < key_arr[pos])) {
			return Error;
		}
		// Shift keys and pointers left
		for (i=pos+1; i < n; i++)
		{
			key_arr[i-1] = key_arr[i];
			p[i] = p[i+1];
		}
		return --ptr->n >= (ptr==root ? 1 : min) ? Success : LessKeys;
	}

	//if found key but p is not a leaf
	if (pos < n && key == key_arr[pos])
	{
		struct node *qp = p[pos], *qp1;
		int nkey;
		while(1)
		{
			nkey = qp->n;
			qp1 = qp->p[nkey];
			if (qp1 == NULL)
				break;
			qp = qp1;
		}
		key_arr[pos] = qp->keys[nkey-1];
		qp->keys[nkey - 1] = key;
	}
	value = del(p[pos], key);
	if (value != LessKeys)
		return value;

	if (pos > 0 && p[pos-1]->n > min)
	{
		pivot = pos - 1; // pivot for left and right node
		lptr = p[pivot];
		rptr = p[pos];
		// Assigns values for right node
		rptr->p[rptr->n + 1] = rptr->p[rptr->n];
		for (i=rptr->n; i>0; i--)
		{
			rptr->keys[i] = rptr->keys[i-1];
			rptr->p[i] = rptr->p[i-1];
		}
		rptr->n++;
		rptr->keys[0] = key_arr[pivot];
		rptr->p[0] = lptr->p[lptr->n];
		key_arr[pivot] = lptr->keys[--lptr->n];
		return Success;
	}
	if (pos < n && p[pos + 1]->n > min)
	{
		pivot = pos; // pivot for left and right node
		lptr = p[pivot];
		rptr = p[pivot+1];
		// Assigns values for left node
		lptr->keys[lptr->n] = key_arr[pivot];
		lptr->p[lptr->n + 1] = rptr->p[0];
		key_arr[pivot] = rptr->keys[0];
		lptr->n++;
		rptr->n--;
		for (i=0; i < rptr->n; i++)
		{
			rptr->keys[i] = rptr->keys[i+1];
			rptr->p[i] = rptr->p[i+1];
		}
		rptr->p[rptr->n] = rptr->p[rptr->n + 1];
		return Success;
	}

	if(pos == n)
		pivot = pos-1;
	else
		pivot = pos;

	lptr = p[pivot];
	rptr = p[pivot+1];
	// merge right node with left node
	lptr->keys[lptr->n] = key_arr[pivot];
	lptr->p[lptr->n + 1] = rptr->p[0];
	for (i=0; i < rptr->n; i++)
	{
		lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
		lptr->p[lptr->n + 2 + i] = rptr->p[i+1];
	}
	lptr->n = lptr->n + rptr->n +1;
	free(rptr); // Remove right node
	for (i=pos+1; i < n; i++)
	{
		key_arr[i-1] = key_arr[i];
		p[i] = p[i+1];
	}
	return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;*/
	return Error;
}

// search
btree_t *search_btree (btree_t *node, uint key, int *pos) {
	uint n = 0;

	if (isempty_btree(node))
		return NULL;

	while ((n < node->n) && (node->keys[n] < key)) 
		n++;
	if (((n+1) > node->n) || (node->keys[n] > key))
		return search_btree(node->p[n], key, pos);
	
	// return position and node
	*pos = n;
	return node;
}

// search key
bool_t search_key_btree (btree_t *node, uint key) {
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

// leaf
bool_t isleaf_btree (btree_t *node) {
	if (node->p[0] == NULL)
		return true;
	return false;
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

// print all btree
void printall_btree (btree_t *node, int tabs) {
	int i;
	if (!isempty_btree(node)) {
		for(i = 1; i <= tabs; i++) {
			printf("\t");
		}
		for (i = 0; i < (node->n); i++) {
			printf("%d ",node->keys[i]);
		}
		printf("\n");
		for (i=0; i <= (node->n); i++) {
			printall_btree(node->p[i], tabs+1);
		}
	}
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
