#include "menu.h"

#define BUFSIZE 256

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

menu_option_t print_menu(void) {
    char buf[BUFSIZE];

    // Clear console print-outs
    system("clear");

    // Print user options
    printf ("Cadastro de Alunos\n");
    printf ("------------------------------------\n");
    printf ("ALUNOS\n");
    printf ("1: Inserir\n");
    printf ("2: Alterar\n");
    printf ("3: Buscar\n");
    printf ("4: Remover\n");
    printf ("5: Imprimir\n");
    printf ("------------------------------------\n");
    printf ("9: Carregar Alunos do Arquivo\n");
    printf ("------------------------------------\n");
    printf ("0: Sair do Programa\n");
    printf ("------------------------------------\n");
    printf ("Opção: ");

    // Read user option
    fgets (buf, BUFSIZE, stdin);
    printf ("\n");

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
        return Remove_Student;
    }
    else if (buf [0] == '5') {
        return Print_Student;
    }
    else if (buf [0] == '9') {
        return Read_File;
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

uint enter_student_id_menu(void) {
    char buf[BUFSIZE];

    system("clear");

    printf ("------------------------------------\n");
    printf("Entre com a matrícula do estudante: ");
    
    fgets (buf, BUFSIZE, stdin);
    return atoi(buf);
}

btree_data_t *enter_student_data_menu(void) {
    btree_data_t * student_data = malloc(sizeof(btree_data_t));
    char buf[BUFSIZE];

    system("clear");

    printf ("------------------------------------\n");
    printf("Entre com o nome do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->name, buf);
    remove_char(student_data->name, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o sexo do estudante (F ou M): ");
    fgets (buf, BUFSIZE, stdin);
    if (buf[0] == '\n') {
        buf[0] = ' ';
    }
    (*student_data).sex = buf[0];

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o RG do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->id, buf);
    remove_char(student_data->id, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o CPF do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->tax_id, buf);
    remove_char(student_data->tax_id, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o número de telefone do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->tel, buf);
    remove_char(student_data->tel, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o número do celular do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->cel, buf);
    remove_char(student_data->cel, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o email do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->email, buf);
    remove_char(student_data->email, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com o endereço do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->address, buf);
    remove_char(student_data->address, '\n');

    printf("\n");
    printf("------------------------------------\n");
    printf("Entre com a data de nascimento do estudante: ");
    fgets (buf, BUFSIZE, stdin);
    strcpy(student_data->birthday, buf);
    remove_char(student_data->birthday, '\n');

    return student_data;
} 

void search_student(btree_t* root) {
    int pos;
    char buf[BUFSIZE];
    btree_t *node = init_btree();

    system("clear");

    printf ("------------------------------------\n");
    printf("Entre com a matrícula do estudante: ");
    
    fgets (buf, BUFSIZE, stdin);
    node = search_btree (root, atoi(buf), &pos);
    if ( node == NULL ) {
        system("clear");

        printf("Aluno não existe!");
        wait_key(buf);
    }
    else {
        system("clear");

        printf ("------------------------------------\n");
        printf("Aluno encontrado!\n");
        printf ("------------------------------------\n");

        printf("              Nome: %s\n",node->datas[pos].name);
        printf("              Sexo: %c\n",node->datas[pos].sex);
        printf("                RG: %s\n",node->datas[pos].id);
        printf("               CPF: %s\n",node->datas[pos].tax_id);
        printf("               Tel: %s\n",node->datas[pos].tel);
        printf("               Cel: %s\n",node->datas[pos].cel);
        printf("             Email: %s\n",node->datas[pos].email);
        printf("          Endereço: %s\n",node->datas[pos].address);
        printf("Data de Nascimento: %s\n",node->datas[pos].birthday);

        printf ("------------------------------------\n");

        wait_key(buf);
    }
}

void print_students(btree_t * root) {
    char buf[BUFSIZE];

    system("clear");
    printf ("------------------------------------\n");
    inorder_btree(root);
    printf ("------------------------------------\n");
    printLevelOrder(root);
    printf ("------------------------------------\n");
    printf("Exiting\n");
    printf("Altura: %d\n", btree_height(root));

    wait_key(buf);
}

btree_t * read_students_file(btree_t * root) {
    uint key;

    FILE * f_ptr;           // ponteiro para o arquivo
    char * f_name = NULL;   // ponteiro para no nome do arquivo
    char * f_line = NULL;   // ponteiro para a linha do arquivo texto
    size_t f_len;           // tamanho da linha do arquivo texto

    f_name = "db/input.txt";
    f_ptr = fopen(f_name, "r");
    if (f_ptr == NULL) {
        printf("Invalid input file\n");
        exit(EXIT_FAILURE);
    }
    
    while (getline(&f_line, &f_len, f_ptr) > 0) {
        btree_data_t *data_s = (btree_data_t*)(malloc(sizeof(btree_data_t)));

        char * ptr_char = (char *)f_line;
        remove_char(f_line, '\n');

        ptr_char = strtok((char *)f_line, ";");
        key = (int)atoi((char *)ptr_char);

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->name, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            (*data_s).sex = *ptr_char;
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->tax_id, ptr_char);
        }
        
        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->id, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->tel, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->cel, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->email, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->address, ptr_char);
        }

        ptr_char = strtok((char *)NULL, ";");
        if (ptr_char != NULL) {
            strcpy(data_s->birthday, ptr_char);
        }

        root = insert_btree(root, (uint)key, data_s);

        free(data_s);
    }

    fclose(f_ptr);
    if (f_line)
        free(f_line);

    return root;
}
