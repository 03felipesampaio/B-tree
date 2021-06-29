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

void print_pagina(PAGINA *pg) {
  printf("Elementos da pag:  ");
  for(int i = 0; i < pg->num_keys; i++) {
    printf("[KEY = %d RRN = %ld] ", pg->keys[i], pg->rrns[i]);
  }
  printf("\n");
}

int main() {
  limpa_arvore();
  ARVORE *arv = cria_arvore();
  inserir_btree(arv, 5 , 1);
  inserir_btree(arv, 43, 2);
  inserir_btree(arv, 12, 3);
  PAGINA *p1 = le_pagina(arv->rrn_raiz);
  print_pagina(p1);
  PAGINA *p2 = le_pagina(p1->prox_paginas[0]);
  print_pagina(p2);
  PAGINA *p3 = le_pagina(p1->prox_paginas[1]);
  print_pagina(p3);
  inserir_btree(arv, 65, 4);
  inserir_btree(arv, 76, 5);
  inserir_btree(arv, 26, 6);
  inserir_btree(arv, 80, 7);
  inserir_btree(arv, 16, 8);
  inserir_btree(arv, 64, 9);
  inserir_btree(arv, 8 , 10);
  inserir_btree(arv, 1 , 11);
  // PAGINA *p1 = le_pagina(arv->rrn_raiz);
  // PAGINA *p2 = le_pagina(p1->prox_paginas[0]);
  // PAGINA *p3 = le_pagina(p2->prox_paginas[0]);
  // PAGINA *p4 = le_pagina(p2->prox_paginas[1]);
  // PAGINA *p5 = le_pagina(p2->prox_paginas[2]);
  // PAGINA *p6 = le_pagina(p1->prox_paginas[1]);
  // PAGINA *p7 = le_pagina(p6->prox_paginas[0]);
  // PAGINA *p8 = le_pagina(p6->prox_paginas[1]);
  // print_pagina(p1);
  // print_pagina(p2);
  // print_pagina(p3);
  // print_pagina(p4);
  // print_pagina(p5);
  // print_pagina(p6);
  // print_pagina(p7);
  // print_pagina(p8);
  /* int a;
  a = busca_btree(arv, 43);
  printf("Posicao %d\n", a);
  a = busca_btree(arv, 16);
  printf("Posicao %d\n", a);
  a = busca_btree(arv, 76);
  printf("Posicao %d\n", a);
  a = busca_btree(arv, 12);
  printf("Posicao %d\n", a);
  a = busca_btree(arv, 1);
  printf("Posicao %d\n", a);
  a = busca_btree(arv, 65);
  printf("Posicao %d\n", a);
  salva_arvore(arv); */

 /*  PAGINA *p1 = ler_pagina(arv->rrn_raiz);
  PAGINA *p2 = ler_pagina(p1->prox_paginas[0]);
  PAGINA *p3 = ler_pagina(p2->prox_paginas[0]);
  PAGINA *p4 = ler_pagina(p2->prox_paginas[1]);
  PAGINA *p5 = ler_pagina(p2->prox_paginas[2]);
  PAGINA *p6 = ler_pagina(p1->prox_paginas[1]);
  PAGINA *p7 = ler_pagina(p6->prox_paginas[0]);
  PAGINA *p8 = ler_pagina(p6->prox_paginas[1]);
  // Raiz
  print_pagina(p1);
  // Filho esquerdo
  print_pagina(p2);
  print_pagina(p3);
  print_pagina(p4);
  print_pagina(p5);
  print_pagina(p6);
  // Filho direito
  print_pagina(p7);
  print_pagina(p8); */

  /* 
                          [43, , ]
         [8,   16   ,     ]                [76,    , ]
    [1, 5, ]  [12, , ]  [26, , ]      [64, 65,  ]     [80, , ]
  
   */

  
  /* inserir_btree(arv, 87, 3);
  inserir_btree(arv, 69, 3);
  inserir_btree(arv, 36, 3);
  inserir_btree(arv, 45, 3);
  inserir_btree(arv, 85, 3);
  inserir_btree(arv, 20, 3);
  inserir_btree(arv, 44, 3); */

  

  
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