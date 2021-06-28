/*
Arquivo: utils.c

Autores:
  Álefe Alves Silva - 11218601
  Felipe Sampaio Amorim - 11275050
  Márcio Guilherme Vieira Silva - 11355786
*/

#include "utils.h"

void clean_files() {
    FILE *fp;

    fp = fopen("ARQ_BTREE", "w");
    fclose(fp);

    fp = fopen("ARQ_DAT", "w");
    fclose(fp);
}

void insert(ARVORE *arv) {
    STUDENT *new_student = create_student();
    insert_student(arv, new_student);
    free(new_student);
}

void search(ARVORE *arv) {
    int key;
    
    scanf("%d", &key);
    STUDENT *student = search_student(arv, key);

    print_student(student);
    free(student);
}

void update(ARVORE *arv) {
    STUDENT *up_student = create_student();

    update_student(arv, up_student);
    
    free(up_student);
}

void print_student(STUDENT *s) {
    if(!s) {
      printf("Registro nao encontrado!\n");
      return;
    }

    printf("-------------------------------\n");
    printf("nUSP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", s->nUSP, s->name, s->surname,s->course, s->grade);
    printf("-------------------------------\n");
}