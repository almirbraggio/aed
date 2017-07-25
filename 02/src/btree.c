// Author: Almir Braggio
// jul. 2017

#include "btree.h"

// init
btree_t *init_btree (void) {
	btree_t *root = NULL;
	return root;
}

btree_t* insert_btree (btree_t *r, uint info, btree_data_t *data) {
	// Insere uma chave na árvore B fazendo split da raiz se necessário
	// retorna a nova raiz
	if(isempty_btree(r)) {
		r = malloc(sizeof(btree_t));
		r->keys[0] = info;
		r->p[0] = NULL;
		r->n = 1;
		memcpy(&r->datas[0], data, sizeof(btree_data_t));
	}
	else {
		insere_aux(r, info, data);
		if(overflow(r)) {
			int m;
			btree_data_t * n = malloc(sizeof(btree_data_t));
			
			btree_t* x = split(r, &m, n);
			btree_t* novaRaiz = malloc(sizeof(btree_t));
			novaRaiz->keys[0] = m;
			memcpy(&(novaRaiz->datas[0]), n, sizeof(btree_data_t));
			novaRaiz->p[0] = r;
			novaRaiz->p[1] = x;
			novaRaiz->n = 1;
			return novaRaiz;
		}
	}
	return r;
}

void insere_aux(btree_t* r, uint info, btree_data_t *data) {
	int pos;
	if(!buscaPos(r, info, &pos)){ // chave não está no nó r if(eh_folha(r)) {
		adicionaDireita(r, pos, info, NULL, data);
    }
    else {
      	insere_aux(r->p[pos], info, data);
      	if(overflow(r->p[pos])){
			int m; // valor da chave mediana
			btree_t* aux = split(r->p[pos], &m, data);
			adicionaDireita(r, pos, m, aux, data);
		}
	}
}

void adicionaDireita(btree_t* r, int pos, int k, btree_t* p, btree_data_t *data) {
	int i;
	for(i=r->n; i>pos; i--) {
		r->keys[i] = r->keys[i-1];
		r->p[i+1] = r->p[i];
		r->datas[i] = r->datas[i-1];
	}
	r->keys[pos] = k;
	r->p[pos+1] = p;
	memcpy(&r->datas[pos], data, sizeof(btree_data_t));
	r->n++;
}

// busca a posição em que a chave info está ou estaria em um no ́ // retorna 1 se a chave esta ́ presente ou 0 caso contr ́ario
int buscaPos(btree_t* r, int info, int * pos) {
  	for((*pos)=0; (*pos) < r->n; (*pos)++)
		if(info == r->keys[(*pos)])
			return 1; // chave já está na  árvore
		else if(info < r->keys[(*pos)])
			break; // info pode estar na sub árvore filho[*pos]
	return 0; // chave não está neste nó
}

btree_t* split(btree_t* x, int * m, btree_data_t * n) {
	btree_t* y = (btree_t*) malloc(sizeof(btree_t));
	int q = x->n/2;
	y->n = x->n - q - 1;
	x->n = q;

	*m = x->keys[q]; // chave mediana

	// TODO Rever aqui!
	memcpy(n, &x->datas[q], sizeof(btree_data_t));
	//memcpy(&n, &x->datas[q], sizeof(btree_data_t));

	int i = 0;
	y->p[0] = x->p[q+1];
	for(i = 0; i < y->n; i++){
		y->keys[i] = x->keys[q+i+1];
		y->datas[i] = x->datas[q+i+1];
		y->p[i+1] = x->p[q+i+2];
	}
	return y;
}

bool_t overflow(btree_t *r) {
	if ( r->n >= (M - 1) ) {
		return true;
	}
	return false;
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
	if (node == NULL)
		return true;
	return false;
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
		for (int i=0; i < node->n; i++) {
			inorder_btree(node->p[i]);
			printf("%d ", (int)(node->keys[i]));
			printf("%s ", node->datas[i].name);
		}
		inorder_btree(node->p[node->n]);
	}
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
