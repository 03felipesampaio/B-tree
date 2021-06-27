#ifndef _DATA_
#define _DATA_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"
#define ARQ_DAT "binFiles/estudantes.data"

typedef struct {
    int nUSP;
    char name[30];
    char surname[30];
    char course[30];
    float grade;
} STUDENT;

STUDENT *create_student();
STUDENT search_student(ARVORE *arvore, int key);
void insert_student(ARVORE *arvore, STUDENT *student);
void update_student(ARVORE *arvore, STUDENT student);
void close_file(ARVORE *arv);

#endif