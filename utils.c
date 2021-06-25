#include "utils.h"

void clean_files() {
    // Erase all content in index and data files
    FILE *fp;

    fp = fopen("binFiles/index.bin", "w");
    fclose(fp);

    fp = fopen("binFiles/data.bin", "w");
    fclose(fp);
}

void insert(CLASS *students_class) {
    int nUSP;
    char name[30], course[30], surname[30];
    float grade;

    scanf("%d,%[^,],%[^,],%[^,],%f", &nUSP, name, surname, course, &grade);

    STUDENT *new_student = create_student(nUSP, name, surname, course, grade);

    insert_student(students_class, new_student);

    free(new_student);
}

void search(CLASS *students_class) {
    int key;
    
    scanf("%d", &key);
    STUDENT* student = search_student(students_class, key);
    print_student(student);
    free(student);
}

void delete(CLASS *students_class) {
    int key;
    
    scanf("%d", &key);
    remove_student(students_class, key);
}

void print_student(STUDENT *s) {
  if(!s) {
    printf("Registro nao encontrado!\n");
    return;
  }

  printf("-------------------------------\n");

  printf("USP number: %d\nName: %s\nSurname: %s\nCourse: %s\nTest grade: %.2f\n", 
         s->nUSP, s->name, s->surname,s->course, s->grade);

  printf("-------------------------------\n");
}

void exit_program(CLASS *students_class) {
    close_file(students_class);
}