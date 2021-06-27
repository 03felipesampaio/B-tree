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
    if(busca_btree(arvore, student->nUSP) != -1) {
        printf("O Registro ja existe!\n");
        return;
    }
    
    fseek(ARQ_DAT, 0, SEEK_END);
    insert_index(ARQ_DAT, ftell(students_class->class_file), student->nUSP); //O QUE ESTÁ FUNÇÃO FARIA?
    fwrite(student, sizeof(STUDENT), 1, ARQ_DAT);
    fflush(ARQ_DAT);
    students_class->len++; //ver se vai ficar
}

void update_student(ARVORE *arvore, STUDENT student) {
    long rrn = busca_btree(arvore, key);
    if(rrn == -1) {
        printf("Registro nao encontrado!");
        return;
    }

    fseek(ARQ_DAT, RRN, SEEK_SET);
    write(student, sizeof(STUDENT), 1, ARQ_DAT);
}

void close_file(ARVORE *arv) {
    fclose(students_class->class_file);

    free(students_class);
}