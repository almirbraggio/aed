#ifndef MENU_H
#define MENU_H

#include "btree.h"

/*
 * Enum for the menu options
 */
typedef enum menu_option {
	Insert_Student,
	Update_Student,
	Search_Student,
	Remove_Student,
	Print_Student,
    Menu_Exit,
    Menu_Error
} menu_option_t;

/*
 * Show user menu on console
 */
menu_option_t print_menu(void);

/*
 * Add new student
 */
btree_t *add_student(uint *key);

/*
 * Update student info
 */
void *update_student(void);

/*
 * Search student
 */
btree_t *search_student(void);

/*
 * Print all students
 */
void print_students(void);

#endif