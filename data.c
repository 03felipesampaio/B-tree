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

CLASS *load_students() {
    // Load all students from binFiles/data.bin, but just the RRN
    // and create a classroom struct
    CLASS *students_class = (CLASS*) malloc (sizeof(CLASS));

    students_class->indexes = load_indexes();
    students_class->len = students_class->indexes->len;
    students_class->class_file = fopen("binFiles/data.bin", "r+");
    assert(students_class->class_file);

    return students_class;
}

STUDENT *search_student(CLASS *student_class, int key) {
    STUDENT *student = (STUDENT*) malloc (sizeof(STUDENT));
    int RRN = search_RRN(student_class->indexes, key);

    if(RRN == -1) {
        return NULL;
    }

    fseek(student_class->class_file, RRN, SEEK_SET);
    fread(student, sizeof(STUDENT), 1, student_class->class_file);

    return student;
}

void insert_student(CLASS *students_class, STUDENT *student) {
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

void remove_student(CLASS *students_class, int key) {
    int RRN = search_RRN(students_class->indexes, key);
    if(RRN == -1) return;

    int x = -1;

    fseek(students_class->class_file, RRN, SEEK_SET);
    // Remove logically by switching nUSP to -1 in file
    fwrite(&x, sizeof(int), 1, students_class->class_file);
    // Remove from index list
    remove_index(students_class->indexes, key);
    students_class->len--;
}

void close_file(CLASS *students_class) {
    fclose(students_class->class_file);
    save_index_file(students_class->indexes);

    free(students_class);
}