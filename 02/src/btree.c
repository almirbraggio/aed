// Author: Almir Braggio
// jul. 2017

#include "btree.h"

// init
btree_t *init_btree (void) {
	btree_t *root = NULL;
	return root;
}

// insert
bool_t insert_btree (btree_t *node, uint key) {
	btree_t *new_node = NULL;
	uint up_key = 0;
	enum key_status status = 0;//status_btree(root, key, &up_key, &new_node);
	// duplicate key
	if (status == Duplicate) {
		printf("Key already available\n");
	}
	// new node
	else if (status == Insert_It) {
		btree_t *up_root = node;
		node = (struct btree_node_t *)malloc(sizeof(btree_t));
		node->n = 1;
		node->keys[0] = up_key;
		node->p[0] = up_root;
		node->p[1] = new_node;
		return true;
	}
	return false;
}

// 
/*enum key_status status_btree (struct node_t ptr, int key, int *upKey,struct node_t *newnode) {
    struct node *newPtr, *lastPtr;
    int pos, i, n,splitPos;
    int newKey, lastKey;
    enum KeyStatus value;
    if (ptr == NULL)
    {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    // If keys in node is less than M-1 where M is order of B tree
    if (n < M - 1)
    {
        pos = searchPos(newKey, ptr->keys, n);
        //Shifting the key and pointer right for inserting the new key
        for (i=n; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        //Key is inserted at exact location
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
        ++ptr->n; //incrementing the number of keys in node
        return Success;
    }
    //If keys in nodes are maximum and position of node to be inserted is last
    if (pos == M - 1)
    {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else //If keys in node are maximum and position of node to be inserted is not last
    {
        lastKey = ptr->keys[M-2];
        lastPtr = ptr->p[M-1];
        for (i=M-2; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
    }
    splitPos = (M - 1)/2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode)=malloc(sizeof(struct node));//Right node after split
    ptr->n = splitPos; //No. of keys for left splitted node
    (*newnode)->n = M-1-splitPos;//No. of keys for right splitted node
    for (i=0; i < (*newnode)->n; i++)
    {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if(i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return Insert_It;
}*/


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

// empty
bool_t isempty_bintree (bintree_t node) {
	return (bool_t)(node == NULL);
}

// insert
bintree_t insert_bintree (bintree_t node, data_t data) {
	if (isempty_bintree(node)) {
		node = (struct bintree_node_t *)malloc(sizeof(struct bintree_node_t));
		node->data = data;
		node->left = node->right = NULL; 
	}
	else {
		if (data < node->data)
			node->left = insert_bintree(node->left, data);
		else if (data > node->data)
			node->right = insert_bintree(node->right, data);
	}
	return node;
}

// search
data_t min_bintree (bintree_t node) {
	bintree_t r = node;
	while (r->left != NULL)
		r =  r->left;
	return r->data;
}

data_t max_bintree (bintree_t node) {
	bintree_t r = node;
	while (r->right != NULL)
		r =  r->right;
	return r->data;
}

// prints
void preorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		printf("%d ", node->data);
		preorder_bintree(node->left);
		preorder_bintree(node->right);
	}
	return;
}

void inorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		inorder_bintree(node->left);
		printf("%d ", node->data);
		inorder_bintree(node->right);
	}
	return;
}

void postorder_bintree(bintree_t node) {
	if (!isempty_bintree(node)) {
		postorder_bintree(node->left);
		postorder_bintree(node->right);
		printf("%d ", node->data);
	}
	return;
}
*/