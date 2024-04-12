//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_remocao.h"
#include "../insercao/produto_insercao.h"

int vazia(ARVOREB * r){
    return r->num_chaves == 0;
}

int eh_raiz(ARVOREB * r){
    int is_raiz = 1;

    for(int i = 0; i < r->num_chaves; i++){
        if(r->filho[i] != -1){
            is_raiz = 0;
            return is_raiz;
        }
    }

    return is_raiz;
}

int underflow(ARVOREB * r){
    if (!vazia(r)){
        if (r->num_chaves < ORDEM/2 && !eh_raiz(r))
            return 1;
        return 0;
    }
    return 0;
}

void remover_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    int codigo, pos_codigo, pos_raiz, pos_esq, pos_dir;

    printf ("Insira o codigo a ser removido: ");
    scanf ("%d", &codigo);

    pos_codigo = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);

    if(cab_indices->pos_raiz == -1){
        printf("A arvore encontra-se vazia!\n");
        free(cab_indices);
        return;
    } else if (pos_codigo == -1) {
        printf("Produto nao encontrado na arvore!\n");
        free(cab_indices);
        return;
    }

    ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);
    pos_raiz = cab_indices->pos_raiz;
    pos_esq = ;
    pos_dir = ;
    remover(files, raiz, pos_raiz, pos_esq, pos_dir, codigo);

    free(raiz);
    free(cab_indices);
}

int pode_emprestar(ARVOREB * r){
    if (r != NULL){
        if (r->num_chaves > ORDEM/2)
            return 1;
        return 0;
    }
    return 0;
}

ARVOREB * find_irmao_esq(FILE* file_indices, ARVOREB * filho){
    return NULL;
}

ARVOREB * find_irmao_dir(FILE *pIobuf, ARVOREB *pNode) {
    return NULL;
}

int is_emprestimo(FILE* file_indices, ARVOREB * r){

    ARVOREB * esq = find_irmao_esq(file_indices,r);
    ARVOREB * dir = find_irmao_dir(file_indices,r);

    if (pode_emprestar(esq) || pode_emprestar(dir))
    {
        free(esq);
        free(dir);
        return 1;
    }
    free(esq);
    free(dir);
    return 0;

}

void realizar_balanceamento(ARQUIVOS files, ARVOREB * r){
    if (is_emprestimo(files.file_indices, r)){//se pode emprestar, faz a redistribuição
        redistribuir(arqArv, r);
    } else {//nao da pra emprestar, faz concatenação
        concatenar(arqArv, r);
    }
}

void remover(ARQUIVOS files, int pos_raiz, int pos_esq, int pos_dir, int codigo){

}