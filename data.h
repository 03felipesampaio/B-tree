/* #ifndef _DATA_
#define _DATA_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"

typedef struct {
    int nUSP;
    char name[30];
    char surname[30];
    char course[30];
    float grade;
} STUDENT;

// Classroom struct
typedef struct {
    INDEX_LIST *indexes;
    FILE *class_file;
    int len;
} CLASS;

STUDENT *create_student(int nUSP, char name[], char surname[], char course[], float grade);
CLASS *load_students();
STUDENT *search_student(CLASS *student_class, int key);
void insert_student(CLASS *students_class, STUDENT *student);
void remove_student(CLASS *students_class, int key);
void close_file(CLASS *students_class);

#endif */