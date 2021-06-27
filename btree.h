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
#define MAX_KEYS 3

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

ARVORE *cria_arvore();
void inserir_btree(ARVORE *arvore, int key, long rrn_reg);
PAGINA *le_pagina(long rrn);
long busca_btree(ARVORE *arvore, int key);
void salva_arvore(ARVORE *arvore);

#endif
