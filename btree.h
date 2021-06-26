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

#define ARQ_BTREE "binFiles/btree.dat"
#define MAX_KEYS 3

typedef struct registro {
  int key;
  long rrn;
} REGISTRO;

typedef struct pagina {
  short num_keys;
  // REGISTRO vetor[MAX_KEYS];
  int keys[MAX_KEYS];
  long rrns[MAX_KEYS];
  long prox_paginas[MAX_KEYS+1];
} PAGINA;

typedef struct header {
  long rrn_raiz;
  int m; // Numero de elementos por pagina
} ARVORE;

ARVORE *cria_arvore();
void inserir_btree(ARVORE *arvore, int key);
PAGINA *ler_pagina(long rrn);
long busca(ARVORE *btree, int key); // TODO

/* Desconsiderar a partir daqui */
















typedef struct {
  int key;
  int pos;
} INDEX;

typedef struct {
  INDEX *list;
  int len;
} INDEX_LIST;

INDEX_LIST *load_indexes();
int search_RRN(INDEX_LIST *indexes, int key);
void insert_index(INDEX_LIST *indexes, int RRN, int key);
void remove_index(INDEX_LIST *indexes, int key);
void save_index_file(INDEX_LIST *indexes);

#endif
