#include "utils.h"

void clean_files() {
    // Erase all content in index and data files
    FILE *fp;

    fp = fopen("binFiles/index.bin", "w");
    fclose(fp);

    fp = fopen("binFiles/data.bin", "w");
    fclose(fp);
}

void insert(ARVORE *arv) {
    STUDENT student;

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
    STUDENT student;

    scanf("%d,%[^,],%[^,],%[^,],%f", &student.nUSP, student.name, student.surname, student.course, &student.grade);

    /*Update Function*/
    update_student(arv, student);
    
    /*testando se o update deu bom*/
    search_student(arv, student.nUSP);
}

void print_student(STUDENT *s) {
    if(!s) {
      printf("Registro nao encontrado!\n");
      return;
    }

    printf("-------------------------------\n");

    printf("USP number: %d\nName: %s\nSurname: %s\nCourse: %s\nTest grade: %.2f\n", s->nUSP, s->name, s->surname,s->course, s->grade);

    printf("-------------------------------\n");
}

void exit_program(ARVORE *arv) {
    close_file(students_class);
}

//funções para teste
void limpa_arvore() {
  FILE *fp = fopen(ARQ_BTREE, "w");
  fclose(fp);
}

void print_pagina(PAGINA *pg) {
  printf("Elementos da pag:  ");
  for(int i = 0; i < pg->num_keys; i++) {
    printf("%d ", pg->keys[i]);
  }
  printf("\n");
}
