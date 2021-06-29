#include "btree.h"

long append_pagina(PAGINA *nova_pagina);
void atualiza_raiz(ARVORE *arvore, int key, long rrn, long primeira_metade, long segunda_metade);
int inserir(long rrn_pag, int *key, long *rrn_reg, long *filho_direito_promovido);
int busca_binaria(PAGINA *pagina, int key);
void inserir_na_pagina(PAGINA *pagina, int key, long rrn, long filho_direito);
void reescreve_pagina(long rrn, PAGINA* pagina);
void split(PAGINA *pagina_atual, long *filho_direito_promovido, int *key, long *rrn) ;
long busca(long rrn, int key);

void salva_arvore(ARVORE *arvore) {
    FILE *fp = fopen(ARQ_BTREE, "r+");

    fwrite(arvore, sizeof(ARVORE), 1, fp);
    fclose(fp);

    free(arvore);
}

// Funcao auxiliar para inserir na btree
void inserir_btree(ARVORE *arvore, int key, long rrn_reg) {
    int flag; // Flag da funcao inserir
    long segunda_metade = 0; // Filho direito do elemento promovido

    // Chama funcao principal
    flag = inserir(arvore->rrn_raiz, &key, &rrn_reg, &segunda_metade);

    // Nesse caso houve uma promocao na raiz, devemos criar outra raiz
    if(flag == PROMOVIDA) {
        atualiza_raiz(arvore, key, rrn_reg, arvore->rrn_raiz, segunda_metade);
    }
}

int inserir(long rrn_pag, int *key, long *rrn_reg, long *filho_direito_promovido) {
    PAGINA *pagina_atual;
    int flag, pos;
    
    // Condicao de parada da recursao
    if(rrn_pag == 0) {
        return PROMOVIDA;
    }

    // Le a pagina no arquivo
    pagina_atual = le_pagina(rrn_pag);
    
    // Encontra posicao de insercao
    pos = busca_binaria(pagina_atual, *key);
    if(pagina_atual->keys[pos] == *key) {
        printf("A key ja estra inserida\n");
        return ERRO;
    }

    flag = inserir(pagina_atual->prox_paginas[pos], key, rrn_reg, filho_direito_promovido);

    // Caso nao haja promocao ou haja erro
    if(flag != PROMOVIDA) {
        free(pagina_atual);
        return NAO_PROMOVIDA;
    }

    // Se ha promocao e a pagina atual nao esta cheia
    if(pagina_atual->num_keys < MAX_KEYS) {
        inserir_na_pagina(pagina_atual, *key, *rrn_reg,*filho_direito_promovido);
        reescreve_pagina(rrn_pag, pagina_atual);
        free(pagina_atual);
        return NAO_PROMOVIDA;
    } else { // Caso a pagina atual esteja cheia
        split(pagina_atual, filho_direito_promovido, key, rrn_reg);
        reescreve_pagina(rrn_pag, pagina_atual);
        free(pagina_atual);
        return PROMOVIDA;
    }
}

void split(PAGINA *pagina_atual, long *filho_direito_promovido, int *key, long *rrn) {
    
    int MIN_KEYS = MAX_KEYS / 2; // Numero minimo de chaves em uma pagina
    
    PAGINA *primeira_metade = pagina_atual;
    PAGINA *segunda_metade = (PAGINA *) calloc(1, sizeof(PAGINA));

    int pos = busca_binaria(pagina_atual, *key);
    
    int vetor_extendido_keys[MAX_KEYS+1]; // Auxiliar para keys
    long vetor_extendido_rrns[MAX_KEYS+1]; // Auxiliar para rrns dos registros
    long vetor_extendido_filhos[MAX_KEYS+2]; // Auxiliar para proximas paginas


    // Copia itens para vetores
    memcpy(&vetor_extendido_keys, &pagina_atual->keys, sizeof(int) * MAX_KEYS);
    memcpy(&vetor_extendido_rrns, &pagina_atual->rrns, sizeof(long) * MAX_KEYS);
    memcpy(&vetor_extendido_filhos, &pagina_atual->prox_paginas, sizeof(long) * (MAX_KEYS+1));
    
    // Insere key e filho direito promovidos nos vetores
    // Key
    memcpy(&vetor_extendido_keys[pos+1], &vetor_extendido_keys[pos], sizeof(int) * (MAX_KEYS - pos));
    vetor_extendido_keys[pos] = *key;
    // RRN
    memcpy(&vetor_extendido_rrns[pos+1], &vetor_extendido_rrns[pos], sizeof(long) * (MAX_KEYS - pos));
    vetor_extendido_rrns[pos] = *rrn;
    // Filho direito
    memcpy(&vetor_extendido_filhos[pos+2], &vetor_extendido_filhos[pos+1], sizeof(long) * (MAX_KEYS - pos));
    vetor_extendido_filhos[pos+1] = *filho_direito_promovido;

    // Separa a pagina atual em duas partes
    // Primeira pagina
    memcpy(primeira_metade->keys, &vetor_extendido_keys[0], sizeof(int) * (MAX_KEYS - MIN_KEYS));
    memcpy(primeira_metade->rrns, &vetor_extendido_rrns[0], sizeof(long) * (MAX_KEYS - MIN_KEYS));
    memcpy(primeira_metade->prox_paginas, &vetor_extendido_filhos[0], sizeof(long) * (MAX_KEYS - MIN_KEYS + 1));
    primeira_metade->num_keys = MAX_KEYS - MIN_KEYS;
    // Segunda pagina
    memcpy(segunda_metade->keys, &vetor_extendido_keys[MAX_KEYS - MIN_KEYS + 1], sizeof(int) * (MIN_KEYS));
    memcpy(segunda_metade->rrns, &vetor_extendido_rrns[MAX_KEYS - MIN_KEYS + 1], sizeof(long) * (MIN_KEYS));
    memcpy(segunda_metade->prox_paginas, &vetor_extendido_filhos[MAX_KEYS - MIN_KEYS + 1], sizeof(long) * (MIN_KEYS+ 1));
    segunda_metade->num_keys = MIN_KEYS;

    // Promove chave
    *key = vetor_extendido_keys[MAX_KEYS - MIN_KEYS];
    *rrn = vetor_extendido_rrns[MAX_KEYS - MIN_KEYS];
    *filho_direito_promovido = append_pagina(segunda_metade);   
}

long busca_btree(ARVORE *arvore, int key) {
    if(!arvore) return ERRO;

    printf("Vai entrar na raiz\n");
    return busca(arvore->rrn_raiz, key);
}

long busca(long rrn, int key) {
    if(rrn == 0) {
        return NAO_ENCONTRADO;
    }

    PAGINA *pagina = le_pagina(rrn);
    long proxima_pagina;

    int pos = busca_binaria(pagina, key);

    if(pagina->keys[pos] != key) {
        proxima_pagina = pagina->prox_paginas[pos];
        free(pagina);
        printf("Vai entrar no filho %d\n", pos);
        return busca(proxima_pagina, key);
    }

    return pagina->rrns[pos];
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
void inserir_na_pagina(PAGINA *pagina, int key, long rrn, long filho_direito) {
    int pos = busca_binaria(pagina, key);

    // Abre espaco para o novo item
    memcpy(&pagina->keys[pos+1], &pagina->keys[pos], sizeof(int) * (pagina->num_keys - pos));
    memcpy(&pagina->rrns[pos+1], &pagina->rrns[pos], sizeof(long) * (pagina->num_keys - pos));
    memcpy(&pagina->prox_paginas[pos+2], &pagina->prox_paginas[pos+1], sizeof(long) * (pagina->num_keys - pos));

    // Insere item na pagina
    pagina->keys[pos] = key;
    pagina->rrns[pos] = rrn;
    pagina->prox_paginas[pos+1] = filho_direito;
    pagina->num_keys++;
    
}

// Atualiza a pagina no arquivo
void reescreve_pagina(long rrn, PAGINA* pagina) {
    FILE *fp = fopen(ARQ_BTREE, "r+");

    fseek(fp, rrn, SEEK_SET);
    fwrite(pagina, sizeof(PAGINA), 1, fp);

    fclose(fp);
}

// Troca a raiz
void atualiza_raiz(ARVORE *arvore, int key, long rrn, long primeira_metade, long segunda_metade) {
    PAGINA *nova_pagina = (PAGINA*) calloc (1, sizeof(PAGINA));

    nova_pagina->keys[0] = key;
    nova_pagina->rrns[0] = rrn;
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
            return meio;
        } else if(key < keys[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return inicio;
}