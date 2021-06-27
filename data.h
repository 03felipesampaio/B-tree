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

STUDENT *create_student(int nUSP, char name[], char surname[], char course[], float grade);
CLASS *load_students();
STUDENT *search_student(CLASS *student_class, int key);
void insert_student(CLASS *students_class, STUDENT *student);
void close_file(CLASS *students_class);

#endif