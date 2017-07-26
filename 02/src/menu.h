#ifndef MENU_H
#define MENU_H

#include "btree.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/*
 * Enum for the menu options
 */
typedef enum menu_option {
	Insert_Student,
	Update_Student,
	Search_Student,
	Remove_Student,
	Print_Student,
	Read_File,
    Menu_Exit,
    Menu_Error
} menu_option_t;

/*
 * Show user menu on console
 */
menu_option_t print_menu(void);

/*
 * Show menu for new student id
 */
uint enter_student_id_menu(void);

/*
 * Show menu for new student data
 */
btree_data_t *enter_student_data_menu(void);

/*
 * Search student
 */
void search_student(btree_t* root);

/*
 * Print all students
 */
void print_students(btree_t * root);

/*
 * Read students from file
 */
btree_t *  read_students_file(btree_t * root);

#endif