/*
Arquivo: main.c

Autores:
  Álefe Alves Silva - 11218601
  Felipe Sampaio Amorim - 11275050
  Márcio Guilherme Vieira Silva - 11355786

Especificações de cada função:
  utils -> funcoes auxiliares para a main
  data  -> administra o arquivo de estudantes
  index -> administra o index dos registros
*/

#include "btree.h"
#include "data.h"
#include "utils.h"

int main() {
  clean_files();

  ARVORE *arv = cria_arvore();

  char comando[15];

  scanf("%s", comando);

  while (strcmp("exit", comando)) {

    if (!strcmp("insert", comando)) insert(arv);
    else if (!strcmp("search", comando)) search(arv);
    else if (!strcmp("update", comando)) update(arv);

    scanf("%s", comando);
  }

  salva_arvore(arv);

  return 0;
}