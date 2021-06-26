#ifndef _UTILS_
#define _UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"
#include "data.h"

void clean_files();
void insert(ARVORE *arv);
void search(ARVORE *arv);
void update(ARVORE *arv);
void exit_program(ARVORE *arv);
void print_student(PAGINA *page);

#endif