//
// Created by andre on 29/04/2024.
//

#include "arvore_utils.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../impressao/produto_impressao.h"
#include <stdio.h>
#include <stdlib.h>

//verifica se um nó(lido) é nulo(arvore vazia)
//pre-condiçao: nó lido
//pos-condiçao: 0 se nao for vazia, !=0 se vazia
int vazia(ARVOREB * r) {
    return (r == NULL);
}

//verifica se o no e folha
//prè-condiçao: no nao nulo
//pos-conidçao: 1 = sim, 0 = nao
int eh_folha(ARVOREB * r) {
    return r->filho[0] == -1;
}

//testa se é raiz
//pre-condição: r nao pode ser NULL
//pos-condição: 1 se for raiz, 0 se nao for
int eh_raiz(FILE * file_indices, ARVOREB * r) {
    if (r != NULL) {
        printf("\n---> BUscandao PAI da chave => %d", r->chave[0]);
        int pos_pai = buscar_pai(file_indices, r->chave[0]);
        if ( pos_pai == -1) {
            return 1;
        }
    }
    return 0;
}

int underflow(FILE * file_indices, ARVOREB * r) {
    if (r != NULL) {
        printf("\n---> no nao e nulo para verificar UNDERFLOW!");
        printf("\n---> Resultado de: (r->num_chaves < MIN = %d) e Resultado de (!eh_raiz(file_indices, r) = %d) ", r->num_chaves < MIN, !eh_raiz(file_indices, r));
        if (r->num_chaves < MIN && !eh_raiz(file_indices, r) ){
            printf("\n---> reotnando 1 no UNDERFLOW!");
            return 1;
        }
        return 0;
    }
    return 0;
}

int buscar_pos_chave(ARVOREB * r, int codigo){
    int pos_codigo;

    // Encontra a pos dentro do nó
    for(pos_codigo = 0; pos_codigo < r->num_chaves; pos_codigo++){
        if( r->chave[pos_codigo] == codigo)
            return pos_codigo;
    }

    return -1;
}

int buscar_pos_filho(ARVOREB * r, int pos){
    int filho;

    // Encontra a pos dentro do nó
    for(filho = 0; filho <= r->num_chaves; filho++){
        if(r->filho[filho] == pos)
            return filho;
    }

    return -1;
}

int mais_chaves_que_min(ARVOREB * r){
    return r->num_chaves > MIN;
}


// Função para verificar se já existe um determinado código na árvore e retorna a posição do nó onde ele está presente
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

int buscar_no_aux(FILE * file_indices, int codigo, int pos){
    if(pos == -1){
        printf("\n---> a funcao buscra no retornour -1");
        return -1;
    }

    ARVOREB * r = ler_no(file_indices, pos);
    imprimir_no(r);
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

//acha a posiçao da chave divisa entre irmao esq e irmao dir.
//pre-condição: os 2 irmãos devem ser filhos do memsmo pai.
//pos-condição: devolve o indice da chave que é divisa no pai entre os nós, ou -1 caso de erro.
int buscar_pos_chave_separadora(FILE* file_indices, ARVOREB * esq, ARVOREB * dir) {//irmao esq e irmão dir
    int pos_pai, pos_esq, pos_dir;

    pos_pai = buscar_pai(file_indices, esq->chave[0]);
    pos_esq = buscar_no(file_indices, esq->chave[0]);
    pos_dir = buscar_no(file_indices, dir->chave[0]);
    ARVOREB * pai = ler_no(file_indices, pos_pai);

    int pos = -1;
    if (!vazia(pai)) {
        if (pai->filho[0] == pos_esq) { //se o filho esq for igual ao filho[0] no pai, a posicao da chave separadora é 0;
            free(pai);
            return 0;
        } else if (pai->filho[pai->num_chaves] == pos_dir) {
            pos = pai->num_chaves - 1;
            free(pai);
            return pos;
        }
        int i = 0;
        for (i = 0; i < pai->num_chaves; i++)
        {
            if (pos_esq == pai->filho[i] && pos_dir == pai->filho[i + 1])
            {
                free(pai);
                return i;
            }
        }
        return -1;
    }
    return -1;
}

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
    return buscar_pai_by_pos_aux(file_indices, pos_raiz, pos);

}

int buscar_pai_by_pos_aux(FILE * file_indices, int pos_raiz, int pos){
    ARVOREB * r = ler_no(file_indices, pos_raiz);

    int i;
    for (i = 0; i <= r->num_chaves; i++) {
        if (r->filho[i] == pos) {
            free(r);
            return pos_raiz;
        }
    }

    for (i = 0; i <= r->num_chaves; i++) {
        return buscar_pai_aux(file_indices, r->filho[i], pos);
    }

    free(r);
    return -1;
}

//int buscar_pai(ARQUIVOS files, int pos_raiz, int codigo, int *pos_filho_remocao) {
//    ARVOREB *r = ler_no(files.file_indices, pos_raiz);
//
//    // Verifica se é uma folha
//    if (eh_folha(r)) {
//        *pos_filho_remocao = -1; // Marca o filho de remoção como inexistente
//        return -1; // Retorna -1 indicando que não foi encontrado
//    }
//
//    int i;
//    for (i = 0; i < r->num_chaves; i++) {
//        // Se o código for menor que a chave atual, desce para o filho à esquerda
//        if (codigo < r->chave[i]) {
//            ARVOREB *filho = ler_no(files.file_indices, r->filho[i]);
//            int pos_codigo = busca_pos_chave(filho, codigo);
//            free(filho);
//            // Se a chave for encontrada no filho, retorna o nó atual como pai
//            if (pos_codigo != -1) {
//                *pos_filho_remocao = i;
//                return pos_raiz;
//            }
//            // Se não, continua a busca descendente
//            return buscar_pai(files, r->filho[i], codigo, pos_filho_remocao);
//        }
//    }
//
//    // Se o código for maior que todas as chaves, desce para o último filho
//    ARVOREB * filho = ler_no(files.file_indices, r->filho[i]);
//    int pos_codigo = busca_pos_chave(filho, codigo);
//    free(filho);
//
//    // Se a chave for encontrada no último filho, retorna o nó atual como pai
//    if (pos_codigo != -1) {
//        *pos_filho_remocao = i;
//        return pos_raiz;
//    }
//
//    // Se não, continua a busca descendente
//    return buscar_pai(files, r->filho[i], codigo, pos_filho_remocao);
//}