#include "btree.h"

long append_pagina(PAGINA *nova_pagina);
void atualiza_raiz(ARVORE *arvore, int key, long primeira_metade, long segunda_metade);
int inserir(long rrn, int key, long *segunda_metade, int *key_promovida);
int busca_binaria(PAGINA *pagina, int key);
void inserir_na_pagina(PAGINA *pagina, int key, long filho_direito);
void reescreve_pagina(long rrn, PAGINA* pagina);
void split(PAGINA *pagina_atual, long *filho_direito_promovido, int *key) ;

// Funcao auxiliar para inserir na btree
void inserir_btree(ARVORE *arvore, int key) {
    int flag; // Flag da funcao inserir
    int key_promovida; // Key promovida
    long segunda_metade; // Filho direito do elemento promovido

    // Chama funcao principal
    flag = inserir(arvore->rrn_raiz, key, &segunda_metade, &key_promovida);

    // Nesse caso houve uma promocao na raiz, devemos criar outra raiz
    if(flag == PROMOVIDA) {
        atualiza_raiz(arvore, key_promovida, arvore->rrn_raiz, segunda_metade);
    }
}

int inserir(long rrn, int key, long *filho_direito_promovido, int *key_promovida) {
    PAGINA *pagina_atual;
    int flag, pos;
    
    // Condicao de parada da recursao
    if(rrn == 0) {
        *key_promovida = key;
        *filho_direito_promovido = 0;
        return PROMOVIDA;
    }

    // Le a pagina no arquivo
    pagina_atual = le_pagina(rrn);
    
    // Encontra posicao de insercao
    pos = busca_binaria(pagina_atual, key);
    if(pos == ERRO) {
        printf("A key ja estra inserida\n");
        return ERRO;
    }

    flag = inserir(pagina_atual->prox_paginas[pos], key, filho_direito_promovido, key_promovida);

    // Caso nao haja promocao ou haja erro
    if(flag != PROMOVIDA) {
        return NAO_PROMOVIDA;
    }

    // Se ha promocao e a pagina atual nao esta cheia
    if(pagina_atual->num_keys < MAX_KEYS) {
        inserir_na_pagina(pagina_atual, *key_promovida, *filho_direito_promovido);
        reescreve_pagina(rrn, pagina_atual);
        return NAO_PROMOVIDA;
    } else { // Caso a pagina atual esteja cheia
        split(pagina_atual, filho_direito_promovido, key_promovida);
        reescreve_pagina(rrn, pagina_atual);
        return PROMOVIDA;
    }

}

void split(PAGINA *pagina_atual, long *filho_direito_promovido, int *key) {
    
    int MIN_KEYS = MAX_KEYS / 2;
    
    PAGINA *primeira_metade = pagina_atual;
    PAGINA *segunda_metade = (PAGINA *) calloc(1, sizeof(PAGINA));

    int pos = busca_binaria(pagina_atual, *key);
    
    int vetor_extendido_keys[MAX_KEYS+1];
    long vetor_extendido_filhos[MAX_KEYS+2];


    // Copiar itens para vetores
    memcpy(&vetor_extendido_keys, &pagina_atual->keys, sizeof(int) * MAX_KEYS);
    memcpy(&vetor_extendido_filhos, &pagina_atual->prox_paginas, sizeof(long) * (MAX_KEYS+1));
    
    // Inserir key e filho direito promovidos nos vetores
    memcpy(&vetor_extendido_keys[pos+1], &vetor_extendido_keys[pos], sizeof(int) * (MAX_KEYS - pos));
    vetor_extendido_keys[pos] = *key;
    memcpy(&vetor_extendido_filhos[pos+2], &vetor_extendido_filhos[pos+1], sizeof(long) * (MAX_KEYS - pos));
    vetor_extendido_filhos[pos+1] = *filho_direito_promovido;

    // Separa a pagina atual em duas partes
    memcpy(primeira_metade->keys, &vetor_extendido_keys[0], sizeof(int) * (MAX_KEYS - MIN_KEYS));
    primeira_metade->num_keys = MAX_KEYS - MIN_KEYS;
    memcpy(primeira_metade->prox_paginas, &vetor_extendido_filhos[0], sizeof(long) * (MAX_KEYS - MIN_KEYS + 1));
    
    memcpy(segunda_metade->keys, &vetor_extendido_keys[MIN_KEYS + 2], sizeof(int) * (MIN_KEYS));
    segunda_metade->num_keys = MIN_KEYS;
    memcpy(segunda_metade->prox_paginas, &vetor_extendido_filhos[MIN_KEYS + 2], sizeof(long) * (MIN_KEYS+ 1));

    // Promove chave
    *key = vetor_extendido_keys[MAX_KEYS - MIN_KEYS];
    *filho_direito_promovido = append_pagina(segunda_metade);   
}

long busca(ARVORE *btree, int key) {
    return -1;
}

/* Funcoes auxiliares */

ARVORE *cria_arvore() {
    ARVORE *nova_arvore = (ARVORE*) malloc (sizeof(ARVORE));
    FILE *fp = fopen(ARQ_BTREE, "r+");

    // Caso a arvore exista
    if(fread(nova_arvore, sizeof(ARVORE), 1, fp)) {
        printf("Arvore ja existia\n");
    } else { // Caso a arvore nao exista
        printf("Arvore nao existia\n");
        nova_arvore->rrn_raiz = 0;
        nova_arvore->m = MAX_KEYS;
        fwrite(nova_arvore, sizeof(ARVORE), 1, fp); // Escreve arvore no arquivo
    }

    fclose(fp);
    return nova_arvore;
}

// Escreve pagina no final do arquivo
long append_pagina(PAGINA *nova_pagina) {
    long rrn;
    FILE *fp = fopen(ARQ_BTREE, "a");

    rrn = ftell(fp);
    fwrite(nova_pagina, sizeof(PAGINA), 1, fp);
    fclose(fp);
    return rrn;
}

// Le pagina do arquivo para memoria
PAGINA *le_pagina(long rrn) {
    FILE *fp = fopen(ARQ_BTREE, "r");
    PAGINA *pagina = (PAGINA*) malloc(sizeof(PAGINA));

    fseek(fp, rrn, SEEK_SET);
    fread(pagina, sizeof(PAGINA), 1, fp);
    
    fclose(fp);
    // printf("Leu pagina, primeiro elemento = %d\n", pagina->keys[0]);
    return pagina;
}

// Insere registro no vetor de keys
void inserir_na_pagina(PAGINA *pagina, int key, long filho_direito) {
    int pos = busca_binaria(pagina, key);

    memcpy(&pagina->keys[pos+1], &pagina->keys[pos], sizeof(int) * (pagina->num_keys - pos));
    memcpy(&pagina->prox_paginas[pos+2], &pagina->prox_paginas[pos+1], sizeof(long) * (pagina->num_keys - pos));

    pagina->num_keys++;
    pagina->keys[pos] = key;
    pagina->prox_paginas[pos+1] = filho_direito;
    
}

// Troca a raiz
void atualiza_raiz(ARVORE *arvore, int key, long primeira_metade, long segunda_metade) {
    PAGINA *nova_pagina = (PAGINA*) calloc (1, sizeof(PAGINA));

    nova_pagina->keys[0] = key;
    nova_pagina->prox_paginas[0] = primeira_metade;
    nova_pagina->prox_paginas[1] = segunda_metade;
    nova_pagina->num_keys++;
    // Escreve pagina no final do arquivo
    arvore->rrn_raiz = append_pagina(nova_pagina);
}

int busca_binaria(PAGINA *pagina, int key) {
    int tam = pagina->num_keys;
    int *keys = pagina->keys;

    int inicio = 0, fim = tam - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if(key == keys[meio]) {
            return ERRO;
        } else if(key < keys[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return inicio;
}