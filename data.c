#include "data.h"

STUDENT *create_student() {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));

    scanf("%d,%[^,],%[^,],%[^,],%f", &student->nUSP, student->name, student->surname, student->course, &student->grade);

    return student;
}

STUDENT *search_student(ARVORE *arvore, int key) {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));
    int rrn = busca_btree(arvore, key);

    if(rrn == -1) {
        return NULL;
    }
    //printf("\nRRN: %d\n", rrn);
    FILE *fp = fopen(ARQ_DAT, "r");
    fseek(fp, rrn, SEEK_SET);
    fread(student, sizeof(STUDENT), 1, fp);

    return student;
}

void insert_student(ARVORE *arvore, STUDENT *student) {
    long rrn = busca_btree(arvore, student->nUSP) ;
    if(rrn != NAO_ENCONTRADO) {
        printf("O Registro ja existe!\n");
        return;
    }
    //printf("registro não existe, inserindo no data\n");
    FILE *fp = fopen(ARQ_DAT, "a");
    rrn = ftell(fp);
    fwrite(student, sizeof(STUDENT), 1, fp);
    fclose(fp);
    //printf("\nchamando inserção na btree\n");
    inserir_btree(arvore, student->nUSP, rrn);  
}

void update_student(ARVORE *arvore, STUDENT *student) {
    long rrn = busca_btree(arvore, student->nUSP);
    if(rrn == -1) {
        printf("Registro nao encontrado!");
        return;
    }
    FILE *fp = fopen(ARQ_DAT, "r+");
    fseek(fp, rrn, SEEK_SET);
    fwrite(student, sizeof(STUDENT), 1, fp);
    fclose(fp);
}