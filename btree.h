/*
Arquivo: btree.h

Autores:
  Álefe Alves Silva - 11218601
  Felipe Sampaio Amorim - 11275050
  Márcio Guilherme Vieira Silva - 11355786
*/

#ifndef _INDEX_
#define _INDEX_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define ERRO -1
#define NAO_PROMOVIDA 0
#define PROMOVIDA 1
#define NAO_ENCONTRADO -1

#define ARQ_BTREE "binFiles/btree.dat"
#define MAX_KEYS 204

typedef struct pagina {
  short num_keys;
  int keys[MAX_KEYS];
  long rrns[MAX_KEYS];
  long prox_paginas[MAX_KEYS+1];
} PAGINA;

typedef struct header {
  long rrn_raiz;
  int m; // Numero de elementos por pagina
} ARVORE;

ARVORE *cria_arvore(); //função que retorna um ponteiro para estrutura de árvore
void inserir_btree(ARVORE *arvore, int key, long rrn_reg); //função que insere registro no vetor de keys
PAGINA *le_pagina(long rrn); //função que lê e retorna um ponteiro para uma página inteira
long busca_btree(ARVORE *arvore, int key); //função que faz o retorno para chamadas de procura no arquivo de dados
void salva_arvore(ARVORE *arvore); //

#endif
