// Estrutura de dados
// Authors: Almir Braggio, Guilherme Zat
// May - 2017

#include "lib/fila.h"
#include "lib/pilha.h"
#include "lib/lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

#define TRUE    1
#define FALSE   0

typedef char boolean;

// Estrutura para os alunos
struct Student {
    int id;             // identificação do aluno (RA)
    char name[24];      // nome do aluno
};

// Estruturas para os livros e acervo
struct Book {
    int id;
    char title[32], author[24];      // dados do livro
};

struct Collection {
    int bookcase, stand;                // identificadores da estante e prateleira
    struct Book book;
};

// Estrutura para a sala de estudos
struct Room {
    struct Student student;
    struct Stack *books;
};

// Functions
void print_Waiting(void *_waiting);             // imprime a fila de espera de alunos
void print_Collection (void *_collection);      // imprime o acervo da biblioteca

int search_Book_position (struct List *_list, int _bookcase, int _stand, int _id);                                                  // procura a posição para inserir um livro
boolean insert_Book_position (struct List *_list, int _position, int _bookcase, int _stand, int _id, char *_title, char *_author);  // insere um livro
boolean insert_Book (struct List *_list, int _bookcase, int _stand, int _id, char *_title, char *_author);                          // insere um livro
boolean queue_Student (struct Queue *_queue, int _id, char *_name);                                                                 // coloca um aluno na fila
int search_Book_position_by_id (struct List *_list, int _id);

void remove_char (char * _string, char _char);

// Aguarda uma tecla
void wait_key (char *_a);

void insert_Student_Room (struct Room *_room, int _ra, char *_name);

void print_Room(void *_room);

void insert_Book_Room(void *room, int bookcase, int stand, int id, char *title, char *author);

struct Collection *get_Book_by_id (struct List *_list, int _id);

// Main
int main (int argc, char **argv) {

    int i = 0;
    int bookcase = 0, stand = 0, id = 0, ra = 0;
    char *title = NULL, *author = NULL, *name = NULL;
    char buf[BUFSIZE];

    FILE * f_ptr;           // ponteiro para o arquivo
    char * f_name = NULL;   // ponteiro para no nome do arquivo
    char * f_line = NULL;   // ponteiro para a linha do arquivo texto
    size_t f_len;           // tamanho da linha do arquivo texto

    struct Queue *waiting = init_QUEUE(sizeof(struct Student));   // fila de espera dos alunos
    struct List *books = init_LIST(sizeof(struct Collection));    // lista de livros do acervo

    struct Room room[3];       // lista de salas de estudo

    for (i=0; i<3; i++) {
        void *a = &room[i].student.id;
        memset((void *)a, '\0', sizeof(struct Student));
        room[i].books = init_STACK(sizeof(struct Collection));
    }

    f_name = "db/collection.txt";
    f_ptr = fopen(f_name, "r");
    if (f_ptr == NULL) {
        printf ("Invalid input file\n");
        exit(EXIT_FAILURE);
    }

    i = 0; bookcase = 0; stand = 0; id = 0; ra = 0;
    title = NULL; author = NULL; name = NULL;
    while (getline(&f_line, &f_len, f_ptr) > 0) {
        char * ptr_char = (char *)f_line;
        remove_char(f_line, '\n');

        if (strlen(f_line) == 2) {
            if (f_line[0] == 'E') {
                ptr_char++;
                bookcase = (int)atoi((char *)ptr_char);
            }
            else if (f_line[0] == 'P') {
                ptr_char++;
                stand = (int)atoi((char *)ptr_char);
            }
        }
        else if (strlen(f_line) > 2) {
            const char delimiter[2] = ",";
            ptr_char = strtok((char *)f_line, (const char *)delimiter);
            id = (int)atoi((char *)ptr_char);

            ptr_char = strtok((char *)NULL, (const char *)delimiter);
            title = ++ptr_char;

            ptr_char = strtok((char *)NULL, (const char *)delimiter);
            author = ++ptr_char;

            insert_Book(books,(int)bookcase,(int)stand,(int)id,(char *)title,(char *)author);
        }
    }

    f_name = "db/rooms.txt";
    f_ptr = fopen(f_name, "r");
    if (f_ptr == NULL) {
        printf ("Invalid input file\n");
        exit(EXIT_FAILURE);
    }

    i = 0; bookcase = 0; stand = 0; id = 0; ra = 0;
    title = NULL; author = NULL; name = NULL;
    while (getline(&f_line, &f_len, f_ptr) > 0) {
        char * ptr_char = (char *)f_line;
        remove_char(f_line, '\n');

        if (strlen(f_line) == 2) {
            if (f_line[0] == 'E') {
                ptr_char++;
                bookcase = (int)atoi((char *)ptr_char);
            }
            else if (f_line[0] == 'P') {
                ptr_char++;
                stand = (int)atoi((char *)ptr_char);
            }
        }
        else if (strlen(f_line) > 2) {
            const char delimiter[2] = ",";

            if (f_line[0] == 'S') {
                // Numero da sala
                ptr_char++;
                i = (int)atoi((char *)ptr_char);

                // RA do aluno
                ptr_char++;
                ptr_char = strtok((char *)f_line, (const char *)delimiter);
                ptr_char = strtok((char *)NULL, (const char *)delimiter);
                ra = (int)atoi((char *)ptr_char);

                // Nome do aluno
                ptr_char = strtok((char *)NULL, (const char *)delimiter);
                name = ++ptr_char;

                // Adiciona o aluno na sala
                insert_Student_Room(&room[i], (int)ra, (char *)name);
            }
            else {
                // Id do livro
                ptr_char = strtok((char *)f_line, (const char *)delimiter);
                id = (int)atoi((char *)ptr_char);

                // Titulo do livro
                ptr_char = strtok((char *)NULL, (const char *)delimiter);
                title = ++ptr_char;

                // Autor do livro
                ptr_char = strtok((char *)NULL, (const char *)delimiter);
                author = ++ptr_char;

                // Adiciona o livro na sala
                insert_Book_Room(&room[i], (int)bookcase, (int)stand, (int)id, (char *)title, (char *)author);
            }
        }
    }

    f_name = "db/waiting.txt";
    f_ptr = fopen(f_name, "r");
    if (f_ptr == NULL) {
        printf ("Invalid input file\n");
        exit(EXIT_FAILURE);
    }

    i = 0; bookcase = 0; stand = 0; id = 0; ra = 0;
    title = NULL; author = NULL; name = NULL;
    while (getline(&f_line, &f_len, f_ptr) > 0) {
        char * ptr_char = (char *)f_line;
        remove_char(f_line, '\n');

        const char delimiter[2] = ",";
        ptr_char = strtok((char *)f_line, (const char *)delimiter);
        ra = (int)atoi((char *)ptr_char);

        ptr_char = strtok((char *)NULL, (const char *)delimiter);
        name = ++ptr_char;


        queue_Student(waiting,(int)ra,(char *)name);
    }

    fclose(f_ptr);
    if (f_line)
        free(f_line);

    system("clear");
    // Forever
    while (1) {

    // Imprime o menu inicial
    printf ("Biblioteca\n---\nLIVROS\n1: Inserir\n2: Remover\n3: Buscar");
    printf ("\n---\nSALAS\n4: Locar Sala\n5: Emprestar Livro\n6: Liberar Sala");
    printf ("\n---\nIMPRIMIR\n7: Estantes\n8: Salas\n9: Fila de Espera");
    printf ("\n---\n0: Sair do Programa\nEnter: ");

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
    // Remover um livro
    else if (buf [0] == '2') {
        int pos;
        printf ("Remover Livro\n");

        printf("Entre com o codigo do livro: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        id = atoi(buf);

        pos = search_Book_position_by_id(books, id);

        if (pos == -1)
            printf ("Livro indisponivel!\n");
        else {
            removeElementPosition_LIST(books, pos);
            printf("Livro removido!\n");
        }

        wait_key(buf);
    }
    // Buscar um livro
    else if (buf [0] == '3') {
        struct Collection *abc = NULL;
        printf ("Buscar Livro\n");
        printf("Entre com o codigo do livro: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        id = atoi(buf);

        abc = get_Book_by_id (books, id);

        if (abc == NULL)
            printf ("Livro indisponivel!\n");
        else {
            printf("Estante %d Prateleira %d\n", abc->bookcase, abc->stand);
        }
        wait_key(buf);
    }
    // Locar sala
    else if (buf [0] == '4') {
        boolean roomFree = FALSE;
        printf("Locar Sala\n");
        printf("Entre com o RA: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        ra = atoi(buf);
        printf("Entre com o nome do estudante: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        name = buf;
        remove_char(name, '\n');

        for (i=0; i<3; i++) {
            if (room[i].student.id == 0){
                roomFree = TRUE;
                insert_Student_Room(&room[i], (int)ra, (char *)name);
            }
        }

        if (roomFree == FALSE){
            printf("Adicionado a fila\n");
            queue_Student(waiting,ra,name);
        }
        wait_key(buf);
    }
    // Emprestar livro
    else if (buf [0] == '5') {
        boolean inRoom = FALSE;
        int pos = -1;
        printf("Emprestar Livro\n");
        printf("Entre com o RA do estudante: ");

        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        ra = atoi(buf);

        //Verificar se o aluno está nas salas
        for (i=0; i<3; i++) {
            if (room[i].student.id == ra){
                inRoom = TRUE;
                break;
            }
        }
        if (inRoom == TRUE){
            printf("Entre com o codigo do livro: ");
            if (fgets (buf, BUFSIZE, stdin) == NULL)
                break;
            id = atoi(buf);

            pos = search_Book_position_by_id(books, id);
            if (pos == -1) {
                printf("Livro indisponivel\n");
            }
            else {
                struct Collection *rentedBook = malloc(sizeof(struct Collection));
                rentedBook = (struct Collection *)removeElementPosition_LIST(books, pos);
                insert_Book_Room(&room[i], rentedBook->bookcase, rentedBook->stand, rentedBook->book.id, rentedBook->book.title, rentedBook->book.author);
                printf("Livro (%d) %s do %s foi emprestado para a sala %d\n", rentedBook->book.id, rentedBook->book.title, rentedBook->book.author, i);
            }
        }
        else {
            printf("O aluno nao esta nas salas\n");
        }

        wait_key(buf);
    }
    // Liberar sala de estudos
    else if (buf [0] == '6') {
        boolean inRoom = FALSE;
        printf ("Liberar Sala\n");
        printf("Entre com o RA: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        ra = atoi(buf);

        for (i=0; i<3; i++) {
            if (room[i].student.id == ra){
                inRoom = TRUE;
                break;
            }
        }
        if (inRoom == TRUE) {
            room[i].student.id = 0;
            memset((void *)room[i].student.name, '\0', sizeof(char)*24);

            struct Collection *collection = malloc(sizeof(struct Collection));
            int pos = 0;

            while (!isEmpty_STACK(room[i].books)){
                popElement_STACK(room[i].books, collection);
                pos = search_Book_position(books, collection->bookcase, collection->stand, collection->book.id);
                insert_Book_position(books, pos, collection->bookcase, collection->stand, collection->book.id, collection->book.title, collection->book.author);
            }
            // Alocar novo aluno na sala se tiver na fila
            if (!isEmpty_QUEUE(waiting)) {
                    struct Student *student_entering = malloc(sizeof(struct Student));
                    removeElement_QUEUE((struct Queue *)waiting, student_entering);
                    insert_Student_Room(&room[i], student_entering->id, student_entering->name);
                    printf("O Aluno %s entrou na sala %d\n", student_entering->name, i);
            }
        }
        else {
            printf ("Aluno nao esta nas salas\n");
        }
        wait_key(buf);
    }
    // Imprime o acervo
    else if (buf [0] == '7') {
        printf ("Lista de Livros no Acervo\n");
        print_Collection((void *)books);
        wait_key(buf);
    }
    // Imprime o mapa de salas de estudo
    else if (buf [0] == '8') {
        printf ("Mapa de Salas de Estudo\n");
        // Imprime os dados do aluno e dos livros emprestados em cada sala
        for (i=0; i<3; i++) {
            if (room[i].student.id) {
                print_Room(&room[i]);
                printf("\n");
            }
        }
        wait_key(buf);
    }
    // Imprime a fila de espera
    else if (buf [0] == '9') {
        printf ("Fila de Espera\n");
        print_Waiting((void *)waiting);
        wait_key(buf);
    }
    // Exit
    else if (buf [0] == '0') {

        // Arquivo do acervo
        struct List *ptr_list = NULL;
        struct Collection *ptr_collection = NULL;
        struct NodeList *ptr_nodelist = NULL;
        int _a = 99, _b = 99;

        f_name = "db/collection.txt";
        f_ptr = fopen(f_name, "w");
        if (f_ptr == NULL) {
            printf ("Invalid input file\n");
            exit(EXIT_FAILURE);
        }

        ptr_list = (struct List *)books;
        if (isEmpty_LIST(ptr_list)) {
            fprintf (f_ptr, "\n");
        }
        else {
            ptr_nodelist = (struct NodeList *)ptr_list->head;
            do {
                ptr_collection = (struct Collection *)ptr_nodelist->data;
                // Imprime uma vez a estante
                if (_a != ptr_collection->bookcase) {
                    _a = ptr_collection->bookcase;
                    fprintf (f_ptr, "E%d\n", (unsigned int)_a);
                }
                // Imprime uma vez a prateleira
                if (_b != ptr_collection->stand) {
                    _b = ptr_collection->stand;
                    fprintf (f_ptr, "P%d\n", (unsigned int)_b);
                }
                fprintf (f_ptr, "%d, %s, %s\n", (unsigned int)ptr_collection->book.id, (char *)ptr_collection->book.title, (char *)ptr_collection->book.author);
                ptr_nodelist = ptr_nodelist->next;
            }
            while (ptr_nodelist != NULL);
        }

        // Arquivo da fila de espera
        struct Queue *ptr_queue = NULL;
        struct Student *ptr_student = NULL;
        struct NodeQueue *ptr_nodequeue = NULL;

        f_name = "db/waiting.txt";
        f_ptr = fopen(f_name, "w");
        if (f_ptr == NULL) {
            printf ("Invalid input file\n");
            exit(EXIT_FAILURE);
        }

        ptr_queue = (struct Queue *)waiting;
        if (isEmpty_QUEUE(ptr_queue)) {
            fprintf (f_ptr, "\n");
        }
        else {
            ptr_nodequeue = (struct NodeQueue *)ptr_queue->head;
            do {
                ptr_student = (struct Student *)ptr_nodequeue->data;
                fprintf (f_ptr, "%d, %s\n", (unsigned int)ptr_student->id, (char *)ptr_student->name);
                ptr_nodequeue = ptr_nodequeue->next;
            }
            while (ptr_nodequeue != NULL);
        }

        // Arquivo das salas de estudo
        struct NodeStack *ptr_nodestack = NULL;
        struct Stack *ptr_stack = NULL;
        struct Room *ptr_room = NULL;
        struct Collection *ptr_coll = NULL;

        f_name = "db/rooms.txt";
        f_ptr = fopen(f_name, "w");
        if (f_ptr == NULL) {
            printf ("Invalid input file\n");
            exit(EXIT_FAILURE);
        }

        for (i=0; i<3; i++) {
            ptr_room = (struct Room *)&room[i];
            ptr_stack = (struct Stack *)ptr_room->books;

            fprintf (f_ptr, "S%d, %d, %s\n", i, ptr_room->student.id, ptr_room->student.name);

            if (!isEmpty_STACK(ptr_stack)) {
                ptr_nodestack = ptr_stack->head;
                do {
                    ptr_coll = ptr_nodestack->data;
                    fprintf (f_ptr, "E%d\n", ptr_coll->bookcase);
                    fprintf (f_ptr, "P%d\n", ptr_coll->stand);
                    fprintf (f_ptr, "%d, %s, %s\n", ptr_coll->book.id, ptr_coll->book.title, ptr_coll->book.author);
                    ptr_nodestack = ptr_nodestack->next;
                }
                while (ptr_nodestack != NULL);
            }
        }

        break;
    }
    else
        fprintf (stderr, "Error in input\n");
    }

    return 0;
}

void print_Waiting(void *_waiting) {
    struct Queue *_self = (struct Queue *)_waiting;
    struct Student*_temp = NULL;
    struct NodeQueue *_ptr = NULL;
    int i = 0;

    if (isEmpty_QUEUE(_self)) {
        printf("Is Empty\n");
        return;
    }

    _ptr = (struct NodeQueue *)_self->head;
    do {
        _temp = (struct Student *)_ptr->data;
        printf ("(Pos %d) %d\t%s\n", i++, (unsigned int)_temp->id, (char *)_temp->name);
        _ptr = _ptr->next;
    }
    while (_ptr != NULL);

    printf("\n");
    return;
}

void print_Collection(void *_collection) {
    struct List *_self = (struct List *)_collection;
    struct Collection *_temp = NULL;
    struct NodeList *_ptr = NULL;
    int _a = 99, _b = 99;

    if (isEmpty_LIST(_self)) {
        printf("Is Empty\n");
        return;
    }

    _ptr = (struct NodeList *)_self->head;
    do {
        _temp = (struct Collection *)_ptr->data;
        // Imprime uma vez a estante
        if (_a != _temp->bookcase) {
            _a = _temp->bookcase;
            printf ("E%d\n", (unsigned int)_a);
        }
        // Imprime uma vez a prateleira
        if (_b != _temp->stand) {
            _b = _temp->stand;
            printf ("P%d\n", (unsigned int)_b);
        }
        printf ("%d, %s, %s\n", (unsigned int)_temp->book.id, (char *)_temp->book.title, (char *)_temp->book.author);
        _ptr = _ptr->next;
    }
    while (_ptr != NULL);

    printf("\n");
    return;
}

boolean insert_Book (struct List *_list, int _bookcase, int _stand, int _id, char *_title, char *_author) {
    struct Collection *_temp = (struct Collection *)malloc(sizeof(struct Collection));

    _temp->bookcase = _bookcase;
    _temp->stand = _stand;
    _temp->book.id = _id;

    strcpy(_temp->book.title, _title);
    strcpy(_temp->book.author, _author);

    insertElementBack_LIST((struct List *)_list,(const void *)_temp);

    free(_temp);
    return TRUE;
}

int search_Book_position (struct List *_list, int _bookcase, int _stand, int _id) {
    struct Collection *_temp = NULL;
    struct NodeList *_ptr = NULL;

    int counter = 0;

    // Verifica condição para inserir na primeira posição
    if (isEmpty_LIST(_list)) {
        printf("Is Empty\n");
        return 0;
    }

    _ptr = (struct NodeList *)_list->head;
    while (_ptr != NULL) {
        _temp = (struct Collection *)_ptr->data;
        if (_temp->bookcase > _bookcase){
            return counter;
        }
        else if (_temp->bookcase == _bookcase){
            if (_temp->stand > _stand){
                return counter;
            }
            else if (_temp->stand == _stand) {
                if (_temp->book.id > _id){
                    return counter;
                }
            }
        }
        _ptr = (struct NodeList *)_ptr->next;
        counter++;
    }
    return counter;
}

int search_Book_position_by_id (struct List *_list, int _id) {
    struct NodeList *_ptr = NULL;
    struct Collection *_temp = NULL;
    int counter = 0;

    _ptr = (struct NodeList *)_list->head;

    while (_ptr != NULL) {
        _temp = (struct Collection *)_ptr->data;
        if (_temp->book.id == _id) {
            return counter;
        }
        _ptr = (struct NodeList *)_ptr->next;
        counter++;
    };
    return -1;
}

struct Collection *get_Book_by_id (struct List *_list, int _id) {
    struct NodeList *_ptr = NULL;
    struct Collection *_temp = NULL;

    _ptr = (struct NodeList *)_list->head;

    while (_ptr != NULL) {
        _temp = (struct Collection *)_ptr->data;
        if (_temp->book.id == _id) {
            return _temp;
        }
        _ptr = (struct NodeList *)_ptr->next;
    };
    return NULL;
}

boolean insert_Book_position (struct List *_list, int _position, int _bookcase, int _stand, int _id, char *_title, char *_author) {
    struct Collection *_temp = (struct Collection *)malloc(sizeof(struct Collection));

    _temp->bookcase = _bookcase;
    _temp->stand = _stand;
    _temp->book.id = _id;

    strcpy(_temp->book.title, _title);
    strcpy(_temp->book.author, _author);

    insertElementPosition_LIST((struct List *)_list,(const void *)_temp, (int)_position);

    free(_temp);
    return TRUE;
}

boolean queue_Student (struct Queue *_queue, int _id, char *_name) {
    struct Student *_temp = (struct Student *)malloc(sizeof(struct Student));

    _temp->id = _id;

    strcpy(_temp->name, _name);

    insertElement_QUEUE((struct Queue *)_queue,(const void *)_temp);

    free(_temp);
    return TRUE;
}

// Remove um caracter de uma string
void remove_char (char * _string, char _char) {
    char *_ptr = _string;
    while(*_string != '\0') {
        if(*_string != _char) {
            *_ptr++ = *_string++;
        } else {
            ++_string;
        }
    }
    *_ptr = '\0';
}

// Aguarda uma tecla ser pressionada
void wait_key (char *_a) {
    printf("Aperte Enter...");
    fgets (_a, 2, stdin);
    system("clear");
}

void insert_Student_Room (struct Room *_room, int _ra, char *_name)
{
    struct Room *_ptr = _room;

    _ptr->student.id = _ra;
    strcpy(_ptr->student.name, _name);

    return;
}

void print_Room(void *_room) {

    struct Room *a = (struct Room *)_room;
    struct Stack *s = (struct Stack *)a->books;
    struct NodeStack *ptr;
    struct Collection *_temp = NULL;

    printf ("RA: %d Nome: %s\n", a->student.id, a->student.name);
    printf ("Livros:\n");

    if (isEmpty_STACK(s)) {
        printf("Is Empty\n");
        return;
    }

    ptr = s->head;
    do {
        _temp = ptr->data;
        printf ("E%d P%d - %d, %s, %s\n", _temp->bookcase, _temp->stand, _temp->book.id, _temp->book.title, _temp->book.author);
        ptr = ptr->next;
    }
    while (ptr != NULL);
    return;
}

void insert_Book_Room(void *room, int bookcase, int stand, int id, char *title, char *author) {
    struct Room *ptr = room;
    struct Collection *coll = (struct Collection *)malloc(sizeof(struct Collection));

    coll->bookcase = bookcase;
    coll->stand = stand;
    coll->book.id = id;

    strcpy(coll->book.title, title);
    strcpy(coll->book.author, author);

    pushElement_STACK(ptr->books,(const void *)coll);

    free (coll);
    return;
}
