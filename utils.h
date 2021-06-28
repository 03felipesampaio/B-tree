/*
Arquivo: utils.h

Autores:
  Álefe Alves Silva - 11218601
  Felipe Sampaio Amorim - 11275050
  Márcio Guilherme Vieira Silva - 11355786
*/

#ifndef _UTILS_
#define _UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"
#include "data.h"

void clean_files(); //apaga todo o conteúdo do índice e dos arquivos de dados
void insert(ARVORE *); //função auxiliar para inserção na árvore e no arquivo de dados
void search(ARVORE *); //função auxiliar para busca do RRN na árvore e do estudante no arquivo de dados
void update(ARVORE *); //função auxiliar para atualizar as informações de um aluno no arquivo de dados
void print_student(STUDENT *); //função para printar um estudante

#endif