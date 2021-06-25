/* 
  utils -> funcoes auxiliares para a main
  data  -> administra o arquivo de estudantes
  index -> administra o index dos registros
 */


#include "btree.h"
#include "data.h"
#include "utils.h"

void limpa_arvore() {
  FILE *fp = fopen(ARQ_BTREE, "w");
  fclose(fp);
}

int main() {
  limpa_arvore();
  ARVORE *arv = cria_arvore();
  printf("RRN -> %ld | M -> %d\n", arv->rrn_raiz, arv->m);
  inserir_btree(arv, 3);
  inserir_btree(arv, 1);
  inserir_btree(arv, 2);
  inserir_btree(arv, 1);
  PAGINA *pagina = ler_pagina(arv->rrn_raiz);
  for(int i = 0; i < pagina->num_keys; i++) {
    printf("Elem %d -> %d\n", i, pagina->keys[i]);
  }

  

  
  /* char entrada[15];

  clean_files();
  CLASS *students_class = load_students();

  scanf("%s", entrada);

  while (strcmp("exit", entrada)) {

    if (!strcmp("insert", entrada)) insert(students_class);
    if (!strcmp("search", entrada)) search(students_class);
    if (!strcmp("delete", entrada)) delete(students_class);

    scanf("%s", entrada);
  }

  exit_program(students_class); */

  return 0;
}