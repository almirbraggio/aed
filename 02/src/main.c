// Author: Almir Braggio
// jun. 2017
/*
#include "useful.h"
#include "btree.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

//#define DBG
#define TEST			9

#define isempty(x) 		isempty_btree(x)

// use for check seg faults and memory leaks
// valgrind --leak-check=full ./bin_tree

static void println(const char *fmt, ...) {
	va_list argp;
	
	fputc('\n', stdout);

	va_start(argp, fmt);
	vfprintf(stdout, fmt, argp);
	va_end(argp);
	return;
}

// Main code
int main(int argc, char *argv[]) {
	btree_t *root = init_btree();
	int i = 0, aux = 0;
	bool_t status = false;

#ifdef DBG
	if (isempty(root) == true)
		println("B-Tree is empty.");
#endif

	// random input
	println("Input:\t");
	//srand((unsigned)time(NULL));
	for (i = 0; i < TEST; i++) {
		aux = (int)(rand() % 9);
		status = insert_btree(&root, (uint)aux);
		printf("%d ", aux);
	}

#ifdef DBG
	if (isempty(root) == false)
		println("B-Tree is not empty.");
#endif

	// output in order
	println("Output:\t");
	inorder_btree(root);

	println("Status:");
	println("\tMin %d < Max %d", (int)min_btree(root), (int)max_btree(root));
	println("\tTotal = %d", total_btree(root));

	// print with tabs
	println("Tree:\t");
	printall_btree(root,0);

	// remove test
	remove_btree(&root, (uint)6);
	remove_btree(&root, (uint)2);

	// print again
	println("Tree:\t");
	printall_btree(root,0);

	println("Exiting!\r\n");
	return 0;
}
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "btree.h"

int main(int argc, char *argv[]) {
	btree_t *root = init_btree();
	uint key;
	bool_t status = false;
	menu_option_t user_option = Menu_Error;

	btree_data_t *data_s = (btree_data_t*)(malloc(sizeof(btree_data_t)));
	
	strcpy(data_s->name, "Zat");
	root = insert_btree(root, (uint)2, data_s);

	strcpy(data_s->name, "Almir");
	root = insert_btree(root, (uint)3, data_s);

	strcpy(data_s->name, "Felipe");
	root = insert_btree(root, (uint)4, data_s);

	strcpy(data_s->name, "Danilo");
	root = insert_btree(root, (uint)5, data_s);

	inorder_btree(root);

	/*
	do {

		// Show user options
		user_option = print_menu();

		switch (user_option) {
			case (Insert_Student):
				key = 2;
			
				btree_data_t *data_s = (btree_data_t*)(malloc(sizeof(btree_data_t)));
				strcpy(data_s->name, "Zat");
				strcpy(data_s->id, "800000");

				status = insert_btree(root, (uint)key, data_s);

				btree_data_t *data_s2 = (btree_data_t*)(malloc(sizeof(btree_data_t)));
				strcpy(data_s2->name, "Almir");
				strcpy(data_s2->id, "12312321");
				status = insert_btree(root, (uint)3, data_s2);

				btree_data_t *data_s3 = (btree_data_t*)(malloc(sizeof(btree_data_t)));
				strcpy(data_s3->name, "Felipe");
				strcpy(data_s3->id, "333333");
				status = insert_btree(root, (uint)7, data_s3);

				btree_data_t *data_s4 = (btree_data_t*)(malloc(sizeof(btree_data_t)));
				strcpy(data_s4->name, "Danilo");
				strcpy(data_s4->id, "3333555533");
				status = insert_btree(root, (uint)8, data_s4);
			break;

			case (Update_Student):
			break;

			case (Search_Student):
			break;

			case (Remove_Student):
			break;

			case (Print_Student):
			break;

			case (Menu_Exit):
				printf("Exiting\n");
				inorder_btree(root);
			break;

			default:
				printf("Default\n");
		}

	}  while (user_option != Menu_Exit);
	*/
	return 0;
	
}
