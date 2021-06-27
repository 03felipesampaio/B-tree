#include "data.h"

STUDENT *create_student() {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));

    scanf("%d,%[^,],%[^,],%[^,],%f", &student.nUSP, student.name, student.surname, student.course, &student.grade);

    return student;
}

STUDENT search_student(ARVORE *arvore, int key) {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));
    int rrn = busca_btree(arvore, key);

    if(rrn == -1) {
        return NULL;
    }

    fseek(ARQ_DAT, rrn, SEEK_SET);
    fread(student, sizeof(STUDENT), 1, ARQ_DAT);

    return STUDENT;
}

void insert_student(ARVORE *arvore, STUDENT *student) {
    long rrn = busca_btree(arvore, student->nUSP) ;
    if(rrn != NAO_ENCONTRADO) {
        printf("O Registro ja existe!\n");
        return;
    }
    FILE *fp = fopen(ARQ_DAT, "a");
    rrn = ftell(fp);
    fwrite(student, sizeof(STUDENT), 1, fp);
    fclose(fp);
    inserir_btree(arvore, key, rrn);  
}

void update_student(ARVORE *arvore, STUDENT *student) {
    long rrn = busca_btree(arvore, student->key);
    if(rrn == -1) {
        printf("Registro nao encontrado!");
        return;
    }
    FILE *fp = fopen(ARQ_DAT, "a");
    fseek(fp, rrn, SEEK_SET);
    write(student, sizeof(STUDENT), 1, fp);
}

void close_file(ARVORE *arv) {
    fclose(students_class->class_file);

    free(students_class);
}