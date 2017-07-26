#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "btree.h"

int main(int argc, char *argv[]) {
	btree_t *root = init_btree();
	btree_data_t *data_s = (btree_data_t*)(malloc(sizeof(btree_data_t)));
	uint key;
	int pos;
	menu_option_t user_option = Menu_Error;

	/*
	key = 2;
	strcpy(data_s->name, "Zat");
	strcpy(data_s->id, "800000");
	root = insert_btree(root, (uint)key, data_s);

	key = 7;
	strcpy(data_s->name, "Almir");
	strcpy(data_s->id, "12312321");
	root = insert_btree(root, (uint)key, data_s);

	key = 5;
	strcpy(data_s->name, "Felipe");
	strcpy(data_s->id, "333333");
	root = insert_btree(root, (uint)key, data_s);

	key = 1;
	strcpy(data_s->name, "Danilo");
	strcpy(data_s->id, "3333555533");
	root = insert_btree(root, (uint)key, data_s);

	key = 0;
	root = insert_btree(root, (uint)key, data_s);

	key = 3;
	root = insert_btree(root, (uint)key, data_s);

	key = 4;
	root = insert_btree(root, (uint)key, data_s);

	key = 6;
	root = insert_btree(root, (uint)key, data_s);

	key = 8;
	root = insert_btree(root, (uint)key, data_s);

	key = 9;
	root = insert_btree(root, (uint)key, data_s);
	*/
	do {
		// Show user options
		user_option = print_menu();

		switch (user_option) {
			case (Insert_Student):	
				do {
					key = enter_student_id_menu();
				} while ( search_btree (root, key, NULL) != NULL );
				data_s = enter_student_data_menu();
				root = insert_btree(root, (uint)key, data_s);
			break;

			case (Update_Student):
				do {
					key = enter_student_id_menu();
				} while ( search_btree (root, key, &pos) == NULL );
				memcpy( 
					&search_btree( root, key, &pos)->datas[pos],
					enter_student_data_menu(),
					sizeof(btree_data_t)
				);
			break;

			case (Search_Student):
				search_student(root);
			break;

			case (Remove_Student):
			break;

			case (Print_Student):
				print_students(root);
			break;

			case (Read_File):
				root = read_students_file(root);
			break;

			case (Menu_Exit):
				printf("Exiting\n");
			break;

			default:
				printf("Default\n");
		}

	}  while (user_option != Menu_Exit);
	
	return 0;
	
}
