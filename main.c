/* 
  utils -> funcoes auxiliares para a main
  data  -> administra o arquivo de estudantes
  index -> administra o index dos registros
 */


#include "btree.h"
#include "data.h"
#include "utils.h"

int main() {
  limpa_arvore();
  ARVORE *arv = cria_arvore();

  char comand[15];

  clean_files();

  scanf("%s", comand);

  while (strcmp("exit", comand)) {

    if (!strcmp("insert", comand)) insert(arv);
    else if (!strcmp("search", comand)) search(arv);
    else if (!strcmp("update", comand)) update(arv);

    scanf("%s", comand);
  }
  /*
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

                          [43, , ]
         [8,   16   ,     ]                [76,    , ]
    [1, 5, ]  [12, , ]  [26, , ]      [64, 65,  ]     [80, , ]

  
  inserir_btree(arv, 87);
  inserir_btree(arv, 69);
  inserir_btree(arv, 36);
  inserir_btree(arv, 45);
  inserir_btree(arv, 85);
  inserir_btree(arv, 20);
  inserir_btree(arv, 44); */

  return 0;
}