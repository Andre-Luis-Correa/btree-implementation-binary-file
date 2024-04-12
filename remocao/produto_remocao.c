//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_remocao.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"

#define MIN (ORDEM/2 + ORDEM%2 - 1)

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

    printf("---> Iniciando a remocao da chave %d!\n", codigo);
    ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);
    remover(files, codigo, cab_indices->pos_raiz, pos_codigo);

    free(raiz);
    free(cab_indices);
}

int mais_chaves_que_min(ARVOREB * r){
    return r->num_chaves > MIN;
}

int bus_pos_chave(ARVOREB * r, int codigo){
    int pos_codigo;

    // Encontra a pos dentro do nó
    for(pos_codigo = 0; pos_codigo < r->num_chaves; pos_codigo++){
        if( r->chave[pos_codigo] == codigo)
            return pos_codigo;
    }

    return -1;
}

void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo){
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);

    // A posição dos dados no arq de dados deve ser atualizado
    // folha->pt_dados[pos_codigo] => posição dos dados no file de dados
    int pos_registro = folha->pt_dados[pos_codigo];
    cab_dados->pos_livre = pos_registro;

    printf("\n ---> CASO 1 - ANTES ATT - REMOCAO: \n");
    imprimir_no(folha);

    // Atualiza o cab_dados com a posição livre
    escreve_cabecalho_dados(files.file_dados, cab_dados);

    // Agora realizar a atualização do nó folha
    int i;
    for(i = pos_codigo; i < folha->num_chaves-1; i++){
        folha->chave[i] = folha->chave[i+1];
        folha->pt_dados[i] = folha->pt_dados[i+1];
        folha->filho[i] = folha->filho[i+1];
    }

    // Atualiza o último fiilho
    folha->filho[i] = folha->filho[folha->num_chaves];
    folha->num_chaves--;

    printf("\n ---> CASO 1 - DEPOIS ATT - REMOCAO: \n");
    imprimir_no(folha);

    escreve_no(files.file_indices, folha, pos_remocao);
    free(cab_dados);
}

// 1° CASO: a remoção é feita em um nó folha com número de chaves maior que o mínimo (ORDEM/2)
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao){
    int pos_codigo, i;

    // Encontra a pos dentro do nó
    pos_codigo = bus_pos_chave(no_a_remover, codigo);
    atualiza_no_remocao_folha(files, no_a_remover, pos_remocao, pos_codigo);
}

void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    // Buscar o nó que possui a chave a ser removida a ser removido
    ARVOREB * no_a_remover = ler_no(files.file_indices, pos_remocao);

    // 1° CASO: a remoção é feita em um nó folha com número de chaves maior que o mínimo (ORDEM/2)
    if(mais_chaves_que_min(no_a_remover) && eh_folha(no_a_remover)){
        // Logo, apenas remove a chave do nó, realizando as alterações necessárias e gravando novamente no arquivo
        remover_caso1(files, no_a_remover, codigo, pos_remocao);
    }


    free(cab_indices);
}