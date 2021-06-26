#include "data.h"

STUDENT *create_student(int nUSP, char name[], char surname[], char course[], float grade) {
    STUDENT *new_student = (STUDENT*) malloc (sizeof(STUDENT));

    new_student->nUSP = nUSP;
    new_student->grade = grade;
    strcpy(new_student->name, name);
    strcpy(new_student->surname, surname);
    strcpy(new_student->course, course);

    return new_student;
}

STUDENT *search_student(ARVORE *arvore, int key) {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));
    int RRN = search_RRN(student_class->indexes, key);

    if(RRN == -1) {
        return NULL;
    }

    fseek(student_class->class_file, RRN, SEEK_SET);
    fread(student, sizeof(STUDENT), 1, student_class->class_file);

    return student;
}

void insert_student(ARVORE *arvore, STUDENT *student) {
    if(search_RRN(students_class->indexes, student->nUSP) != -1) {
        printf("O Registro ja existe!\n");
        return;
    }
    
    fseek(students_class->class_file, 0, SEEK_END);
    insert_index(students_class->indexes, ftell(students_class->class_file), student->nUSP);
    fwrite(student, sizeof(STUDENT), 1, students_class->class_file);
    fflush(students_class->class_file);
    students_class->len++;
}

void update_student(ARVORE *arvore, int key) {

}

void close_file(CLASS *students_class) {
    fclose(students_class->class_file);
    save_index_file(students_class->indexes);

    free(students_class);
}