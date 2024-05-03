#include "arvore_utils.h"
#include "cabecalho_indices.h"
#include <stdio.h>
#include <stdlib.h>

// Verifica se uma árvore B está vazia
// Pré-condição: nenhuma
// Pós-condição: retorna 1 se a árvore estiver vazia, 0 caso contrário
int vazia(ARVOREB * r) {
    return (r == NULL);
}

// Verifica se um nó da árvore B é folha
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o nó for uma folha, 0 caso contrário
int eh_folha(ARVOREB * r) {
    return r->filho[0] == -1;
}

// Verifica se um nó é a raiz da árvore B
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó deve ser válida
// Pós-condição: retorna 1 se o nó for a raiz, 0 caso contrário
int eh_raiz(FILE * file_indices, int pos) {
    CABECALHO_INDICES * cab = le_cabecalho_indices(file_indices);

    int pos_pai = buscar_pai_by_pos(file_indices, pos);

    if ( pos_pai == -1) {
        free(cab);
        return 1;
    }

    free(cab);
    return 0;
}

// Busca a posição de uma chave em um nó da árvore B
// Pré-condição: o nó deve existir
// Pós-condição: retorna a posição da chave se encontrada, -1 caso contrário
int buscar_pos_chave(ARVOREB * r, int codigo){
    int pos_codigo;

    // Encontra a pos dentro do nó
    for(pos_codigo = 0; pos_codigo < r->num_chaves; pos_codigo++){
        if( r->chave[pos_codigo] == codigo)
            return pos_codigo;
    }

    return -1;
}

// Busca a posição de um filho em um nó da árvore B
// Pré-condição: o nó deve existir
// Pós-condição: retorna a posição do filho se encontrado, -1 caso contrário
int buscar_pos_filho(ARVOREB * r, int pos){
    int filho;

    // Encontra a pos dentro do nó
    for(filho = 0; filho <= r->num_chaves; filho++){
        if(r->filho[filho] == pos)
            return filho;
    }

    return -1;
}

// Verifica se um nó possui mais chaves que o mínimo exigido
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o número de chaves for maior que o mínimo, 0 caso contrário
int mais_chaves_que_min(ARVOREB * r){
    return r->num_chaves > MIN;
}

// Função para buscar um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do nó se encontrado, -1 caso contrário
int buscar_no(FILE * file_indices, int codigo){
    CABECALHO_INDICES * cab = le_cabecalho_indices(file_indices);
    int pos_raiz = cab->pos_raiz;
    free(cab);
    printf("\n---> pos raiz = %d", pos_raiz);
    if(pos_raiz == -1){
        printf("\n---> a funcao buscra no retornour -1 pos_raiz == -1");
        return -1;
    }

    return buscar_no_aux(file_indices, codigo, pos_raiz);
}

// Função auxiliar para buscar um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do nó se encontrado, -1 caso contrário
int buscar_no_aux(FILE * file_indices, int codigo, int pos){
    if(pos == -1){
        printf("\n---> a funcao buscra no retornour -1");
        return -1;
    }

    ARVOREB * r = ler_no(file_indices, pos);
    int i;

    for(i = 0; i < r->num_chaves; i++){
        if(r->chave[i] == codigo ){
            free(r);
            return pos;
        } else if (r->chave[i] > codigo ){
            int pos_atual = r->filho[i];
            free(r);
            return buscar_no_aux(file_indices, codigo, pos_atual);
        }
    }

    int pos_atual = r->filho[i];
    free(r);

    return buscar_no_aux(file_indices, codigo, pos_atual);
}

// Função para buscar o pai de um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai(FILE * file_indices, int codigo){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(file_indices);
    int pos_raiz = cab_indices->pos_raiz;
    free(cab_indices);

    ARVOREB * r = ler_no(file_indices, pos_raiz);

    if (eh_folha(r) || buscar_pos_chave(r, codigo) != -1) { // A propria raiz é o pai, pois nao tem pai acima
        free(r);
        return -1; // Retorna -1 indicando que não foi encontrado
    }

    free(r);
    return buscar_pai_aux(file_indices, pos_raiz, codigo);
}

// Função auxiliar para buscar o pai de um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_aux(FILE * file_indices, int pos_raiz, int codigo){
    ARVOREB * r = ler_no(file_indices, pos_raiz);

    int i;
    for (i = 0; i < r->num_chaves; i++) {
        // Se o código for menor que a chave atual, desce para o filho à esquerda
        if (codigo < r->chave[i]) {
                ARVOREB * filho = ler_no(file_indices, r->filho[i]);
                int pos_codigo = buscar_pos_chave(filho, codigo);
                free(filho);
                // Se a chave for encontrada no filho, retorna o nó atual como pai
                if (pos_codigo != -1) {
                    return pos_raiz;
                }
                // Se não, continua a busca descendente
                return buscar_pai_aux(file_indices, r->filho[i], codigo);
            }
        }

    // Se o código for maior que todas as chaves, desce para o último filho
    ARVOREB * filho = ler_no(file_indices, r->filho[i]);
    int pos_codigo = buscar_pos_chave(filho, codigo);
    free(filho);

    // Se a chave for encontrada no último filho, retorna o nó atual como pai
    if (pos_codigo != -1) {
        return pos_raiz;
    }

    // Se não, continua a busca descendente
    return buscar_pai_aux(file_indices, r->filho[i], codigo);
}

// Função para buscar o pai de um nó na árvore B a partir de uma posição de nó
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_by_pos(FILE * file_indices, int pos){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(file_indices);
    int pos_raiz = cab_indices->pos_raiz;
    free(cab_indices);

    ARVOREB * r = ler_no(file_indices, pos_raiz);

    if (eh_folha(r) || (pos == pos_raiz) ) { // A propria raiz é o pai, pois nao tem pai acima
        free(r);
        return -1; // Retorna -1 indicando que não foi encontrado
    }

    free(r);
    printf("\n---> indo para recursao encontrar pai filho");
    return buscar_pai_by_pos_aux(file_indices, pos_raiz, pos);

}

// Função auxiliar para buscar o pai de um nó na árvore B a partir de uma posição de nó
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_by_pos_aux(FILE * file_indices, int pos_raiz, int pos) {
    if( pos_raiz != -1 ) {

        ARVOREB * r = ler_no(file_indices, pos_raiz);

        int i, pai = -1; // Inicialize pai com -1 para indicar que não foi encontrado

        // Verifica se a posição está entre os filhos do nó atual
        for (i = 0; i <= r->num_chaves; i++) {
            if (r->filho[i] == pos) {
                free(r);
                return pos_raiz;
            }
        }

        // Caso a posição não seja um dos filhos, procuramos recursivamente nos filhos
        for (i = 0; i <= r->num_chaves; i++) { // Modificado para <=
            pai = buscar_pai_by_pos_aux(file_indices, r->filho[i], pos);
            if (pai != -1) // Se encontrou o pai, encerra o loop
                break;
        }

        free(r);
        return pai;
    }

    return -1;
}