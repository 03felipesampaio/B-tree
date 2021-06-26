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
    printf("%d ", pg->keys[i]);
  }
  printf("\n");
}

int main() {
  limpa_arvore();
  ARVORE *arv = cria_arvore();
  
  inserir_btree(arv, 5);
  inserir_btree(arv, 43);
  inserir_btree(arv, 12);
  inserir_btree(arv, 65);
  inserir_btree(arv, 76);
  inserir_btree(arv, 26);
  inserir_btree(arv, 80);
  inserir_btree(arv, 16);
  inserir_btree(arv, 64);
  inserir_btree(arv, 8);
  inserir_btree(arv, 1);
  PAGINA *p1 = ler_pagina(arv->rrn_raiz);
  PAGINA *p2 = ler_pagina(p1->prox_paginas[0]);
  PAGINA *p3 = ler_pagina(p1->prox_paginas[1]);
  PAGINA *p4 = ler_pagina(p2->prox_paginas[0]);
  PAGINA *p5 = ler_pagina(p2->prox_paginas[1]);
  PAGINA *p6 = ler_pagina(p2->prox_paginas[2]);
  PAGINA *p7 = ler_pagina(p3->prox_paginas[0]);
  PAGINA *p8 = ler_pagina(p3->prox_paginas[1]);
  // Raiz
  print_pagina(p1);
  // Filho esquerdo
  print_pagina(p2);
  print_pagina(p4);
  print_pagina(p5);
  print_pagina(p6);
  // Filho direito
  print_pagina(p3);
  print_pagina(p7);
  print_pagina(p8);

  /* 
                          [43, , ]
         [8,   16   ,     ]                [76,    , ]
    [1, 5, ]  [12, , ]  [26, , ]      [64, 65,  ]     [80, , ]
  
   */

  
  /* inserir_btree(arv, 87);
  inserir_btree(arv, 69);
  inserir_btree(arv, 36);
  inserir_btree(arv, 45);
  inserir_btree(arv, 85);
  inserir_btree(arv, 20);
  inserir_btree(arv, 44); */

  

  
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