#include "btree.h"

long append_pagina(PAGINA *nova_pagina);
void atualiza_raiz(ARVORE *arvore, int key, long primeira_metade, long segunda_metade);
int inserir(long rrn, int key, long *segunda_metade, int *key_promovida);
int busca_binaria(PAGINA *pagina, int key);
void inserir_na_pagina(PAGINA *pagina, int key, long filho_direito);
void reescreve_pagina(long rrn, PAGINA* pagina);

ARVORE *cria_arvore() {
    ARVORE *nova_arvore = (ARVORE*) malloc (sizeof(ARVORE));
    FILE *fp = fopen(ARQ_BTREE, "r+");

    if(fread(nova_arvore, sizeof(ARVORE), 1, fp)) {
        printf("Arvore ja existia\n");
    } else {
        printf("Arvore nao existia\n");
        nova_arvore->rrn_raiz = 0;
        nova_arvore->m = MAX_KEYS;
        fwrite(nova_arvore, sizeof(ARVORE), 1, fp);
    }

    fclose(fp);
    return nova_arvore;
}

// Funcao auxiliar para inserir na btree
void inserir_btree(ARVORE *arvore, int key) {
    int sinal;
    int key_promovida;
    long segunda_metade;

    // Chama funcao principal
    sinal = inserir(arvore->rrn_raiz, key, &segunda_metade, &key_promovida);

    // Nesse caso houve uma promocao na raiz, devemos criar outra raiz
    if(sinal == PROMOVIDA) {
        printf("Deve criar uma raiz\n");
        atualiza_raiz(arvore, key_promovida, arvore->rrn_raiz, segunda_metade);
    }
}

int inserir(long rrn, int key, long *segunda_metade, int *key_promovida) {
    PAGINA *pagina_atual, *nova_pagina;
    int flag;
    long pos, filho_direito_promovido;
    int chave_promovida;
    
    // Condicao de parada da recursao
    if(rrn == 0) {
        printf("Chegou no fundo do poço\n");
        *key_promovida = key;
        *segunda_metade = 0;
        return PROMOVIDA;
    }

    // Le a pagina no arquivo
    pagina_atual = ler_pagina(rrn);
    
    // Encontra posicao de insercao
    pos = busca_binaria(pagina_atual, key);
    if(pos == ERRO) {
        printf("A key ja estra inserida\n");
        return ERRO;
    }

    flag = inserir(pagina_atual->prox_paginas[pos], key, &filho_direito_promovido, &chave_promovida);

    // Caso nao haja promocao ou haja erro
    if(flag != PROMOVIDA) {
        return NAO_PROMOVIDA;
    }

    // Se ha promocao e a pagina atual nao esta cheia
    if(pagina_atual->num_keys < MAX_KEYS) {
        inserir_na_pagina(pagina_atual, chave_promovida, filho_direito_promovido);
        reescreve_pagina(rrn, pagina_atual);
        printf("Esta inserindo a key %d no vetor, na posicao %ld\n", key, pos);
        return NAO_PROMOVIDA;
    } else { // Caso a pagina atual esteja cheia
        // split()
        return PROMOVIDA;
    }

}

// Troca a raiz
void atualiza_raiz(ARVORE *arvore, int key, long primeira_metade, long segunda_metade) {
    PAGINA *nova_pagina = (PAGINA*) calloc (1, sizeof(PAGINA));

    nova_pagina->keys[0] = key;
    nova_pagina->prox_paginas[0] = primeira_metade;
    nova_pagina->prox_paginas[1] = segunda_metade;
    nova_pagina->num_keys++;
    printf("Primeiro elemento -> %d | tam vetor = %d\n", nova_pagina->keys[0], nova_pagina->num_keys);
    // Escreve pagina no final do arquivo
    arvore->rrn_raiz = append_pagina(nova_pagina);
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

void split(PAGINA *pagina_atual, int key, long filho_direito_promovido,
           int *chave_promovida, long *filho_direito, int pos) {
    
    int MIN_KEYS = MAX_KEYS / 2;
    
    PAGINA *primeira_metade = pagina_atual;
    PAGINA *segunda_metade = (PAGINA *) calloc(1, sizeof(PAGINA));
    
    int vetor_extendido_keys[MAX_KEYS+1];
    int vetor_extendido_filhos[MAX_KEYS+2];

    // Copiar itens para vetores
    memcpy(&vetor_extendido_keys, &pagina_atual->keys, sizeof(int) * MAX_KEYS);
    memcpy(&vetor_extendido_filhos, &pagina_atual->prox_paginas, sizeof(long) * (MAX_KEYS+1));
    
    // Inserir a key no vetor
    memcpy(&vetor_extendido_keys[pos+1], &vetor_extendido_keys[pos], sizeof(int) * (MAX_KEYS - pos));
    vetor_extendido_keys[pos] = key;
    memcpy(&vetor_extendido_filhos[pos+2], &vetor_extendido_filhos[pos+1], sizeof(long) * (MAX_KEYS - pos));
    vetor_extendido_filhos[pos+1] = filho_direito_promovido;

    // Separa a pagina atual em duas partes
    memcpy(&primeira_metade->keys, &vetor_extendido_keys[0], sizeof(int) * (MIN_KEYS));
    primeira_metade->num_keys = MIN_KEYS;
    memcpy(&segunda_metade->keys, &vetor_extendido_keys[MIN_KEYS + 1], sizeof(int) * (MIN_KEYS + 1));
    segunda_metade->num_keys = MAX_KEYS - MIN_KEYS;
    memcpy(&primeira_metade->prox_paginas, &vetor_extendido_filhos[0], sizeof(long) * (MAX_KEYS - MIN_KEYS));
    memcpy(&segunda_metade->prox_paginas, &vetor_extendido_filhos[MIN_KEYS + 1], sizeof(long) * (MIN_KEYS - MIN_KEYS + 1));

    // Promove chave
    *chave_promovida = vetor_extendido_keys[MAX_KEYS / 2];
    *filho_direito = append_pagina(segunda_metade);
}

// Le pagina do arquivo para memoria
PAGINA *ler_pagina(long rrn) {
    printf("Tentando ler pagina\n");

    FILE *fp = fopen(ARQ_BTREE, "r");
    PAGINA *pagina = (PAGINA*) malloc(sizeof(PAGINA));

    fseek(fp, rrn, SEEK_SET);
    fread(pagina, sizeof(PAGINA), 1, fp);
    
    fclose(fp);
    printf("Leu pagina, primeiro elemento = %d\n", pagina->keys[0]);
    return pagina;
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

void inserir_na_pagina(PAGINA *pagina, int key, long filho_direito) {
    int pos = busca_binaria(pagina, key);

    memcpy(&pagina->keys[pos+1], &pagina->keys[pos], sizeof(int) * pagina->num_keys - pos);
    memcpy(&pagina->keys[pos+2], &pagina->keys[pos+1], sizeof(int) * pagina->num_keys - pos);

    pagina->num_keys++;
    pagina->keys[pos] = key;
    pagina->prox_paginas[pos+1] = filho_direito;
    
}

void reescreve_pagina(long rrn, PAGINA* pagina) {
    FILE *fp = fopen(ARQ_BTREE, "r+");

    fseek(fp, rrn, SEEK_SET);
    fwrite(pagina, sizeof(PAGINA), 1, fp);

    fclose(fp);
}

/* Desconsiderar a partir daqui */









































INDEX_LIST *create_index_list();
int get_eof(FILE *fp);
int binary_search(INDEX_LIST *indexes, int key);
int search_pos_insert(INDEX_LIST *indexes, int key);

INDEX_LIST *load_indexes() {
    FILE *index_file = fopen("binFiles/index.bin", "r+");
    assert(index_file);

    INDEX_LIST *indexes = create_index_list();

    int end_of_file = get_eof(index_file);

    while ( ftell(index_file) != end_of_file ) {
        indexes->list = (INDEX *) realloc (indexes->list, sizeof(INDEX) * (++indexes->len) );
        fread(&indexes->list[indexes->len - 1], sizeof(INDEX), 1, index_file);
    }
    
    fclose(index_file);
    return indexes;
}

INDEX_LIST *create_index_list() {
    return (INDEX_LIST*) calloc (1, sizeof(INDEX_LIST));
}

int get_eof(FILE *fp) {
    int cur_pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    int eof = ftell(fp);
    fseek(fp, cur_pos, SEEK_SET);

    return eof;
}

int search_RRN(INDEX_LIST *indexes, int key) {
    int pos = binary_search(indexes, key);

    if(pos == -1) {
        return -1;
    }
    
    return indexes->list[pos].pos;
}

int binary_search(INDEX_LIST *indexes, int key) {
    int start = 0, end = indexes->len - 1;
    int mid;

    while (start <= end) {
        mid = (start + end) / 2;

        if(key == indexes->list[mid].key) {
            return mid;
        } else if(key < indexes->list[mid].key) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}

void insert_index(INDEX_LIST *indexes, int RRN, int key) {
    if(binary_search(indexes, key) != -1) {
        return;
    }

    int pos_insert = search_pos_insert(indexes, key);

    indexes->list = (INDEX *) realloc (indexes->list, sizeof(INDEX) * (indexes->len + 1) );

    // Copy bytes foward
    memcpy(&indexes->list[pos_insert + 1], &indexes->list[pos_insert], sizeof(INDEX) * (indexes->len - pos_insert));

    // Insert index on list
    indexes->list[pos_insert].key = key;
    indexes->list[pos_insert].pos = RRN;
    indexes->len++;
}

int search_pos_insert(INDEX_LIST *indexes, int key) {
    int start = 0, end = indexes->len - 1;
    int mid;

    while (start <= end) {
        mid = (start + end) / 2;

        if(key < indexes->list[mid].key) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return start;
}

void remove_index(INDEX_LIST *indexes, int key) {
    int pos_index = binary_search(indexes, key);

    if(pos_index == -1) {
        return;
    }

    memcpy(&indexes->list[pos_index], &indexes->list[pos_index + 1], sizeof(INDEX) * (indexes->len - pos_index));

    indexes->len--;
    indexes->list = (INDEX*) realloc (indexes->list, sizeof(INDEX) * indexes->len);
}

void save_index_file(INDEX_LIST *indexes) {
    FILE *index_file = fopen("binFiles/index.bin", "w");
    fwrite(indexes->list, sizeof(INDEX), indexes->len, index_file);
    fclose(index_file);
    free(indexes);
}