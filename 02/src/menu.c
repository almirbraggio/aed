#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

// Aguarda uma tecla ser pressionada
void wait_key (char *_a) {
    printf("Aperte Enter...");
    fgets (_a, 2, stdin);
    system("clear");
}

menu_option_t print_menu(void) {
    char buf[BUFSIZE];

    // Clear console print-outs
    system("clear");

    // Print user options
    printf ("Cadastro de Alunos\n");
    printf ("---\n");
    printf ("ALUNOS\n");
    printf ("1: Inserir\n");
    printf ("2: Alterar\n");
    printf ("3: Buscar\n");
    printf ("4: Imprimir\n");
    printf ("---\n");
    printf ("0: Sair do Programa\n");
    printf ("---\n");
    printf ("Opção: ");

    // Read user option
    if (fgets (buf, BUFSIZE, stdin) != NULL) {
        system("clear");
    }
    if (buf [0] == '1') {
        return Insert_Student;
    }
    else if (buf [0] == '2') {
        return Update_Student;
    }
    else if (buf [0] == '3') {
        return Search_Student;
    }
    else if (buf [0] == '4') {
        return Print_Student;
    }
    else if (buf [0] == '0') {
        return Menu_Exit;
    }
    else {
        fprintf (stderr, "Opção não existe.\n");
        wait_key(buf);
        return Menu_Error;
    }

}

btree_t *add_student(uint *key) {

}

void *update_student(void) {

}

btree_t *search_student(void) {

}

void print_students(void) {

}

/*
    // Lê uma opção
    if (fgets (buf, BUFSIZE, stdin) == NULL)
        break;
    else
        system("clear");

    // Inserir um livro
    if (buf [0] == '1') {
        struct Collection *abc = malloc(sizeof(struct Collection));
        int pos = 0;
        printf ("Inserir Livro\n");
        printf("Entre com o codigo do livro: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        id = atoi(buf);
        pos = search_Book_position_by_id (books, id);
        if (pos != -1)
            printf ("Codigo duplicado!\n");
        else {
            printf("Estante: ");
            if (fgets (buf, BUFSIZE, stdin) == NULL)
                break;
            bookcase = atoi(buf);

            printf("Prateleira: ");
            if (fgets (buf, BUFSIZE, stdin) == NULL)
                break;
            stand = atoi(buf);

            printf("Entre com o titulo: ");
            //buf = "";
            if (fgets (buf, BUFSIZE, stdin) == NULL)
                break;
            title = malloc(sizeof(char)*32);
            strcpy(title,buf);
            remove_char(title, '\n');

            printf("Entre com o autor: ");
            //buf = "";
            if (fgets (buf, BUFSIZE, stdin) == NULL)
                break;
            author = malloc(sizeof(char)*24);
            strcpy(author,buf);
            remove_char(author, '\n');

            abc->bookcase = bookcase;
            abc->stand = stand;
            abc->book.id = id;
            strcpy(abc->book.title, title);
            strcpy(abc->book.author, author);

            pos = search_Book_position(books, bookcase, stand, id);

            insertElementPosition_LIST (books, abc, pos);

            free(title);
            free(author);
        }
        wait_key(buf);
    }
*/