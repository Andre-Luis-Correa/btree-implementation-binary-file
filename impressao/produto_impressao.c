//
// Created by andre on 08/04/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "produto_impressao.h"
#include "../insercao/produto_insercao.h"

void imprimir_lista_produtos(ARQUIVOS files, int pos_atual) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos_atual == -1) {
        printf("Arvore vazia!\n");
        free(cab_indices);
        return;
    }else{
        ARVOREB *no = ler_no(files.file_indices, pos_atual);

        for (int i = 0; i <= no->num_chaves; i++) {
            imprimir_lista_produtos(files, no->filho[i]);

            if (i != no->num_chaves) {
                DADOS_REGISTRO *registro = ler_registro(files.file_dados, no->pt_dados[i]);
                printf("Codigo: %d, Nome: %s\n", registro->produto.codigo, registro->produto.nome);
                free(registro);
            }
        }

        free(no);
        free(cab_indices);
    }

}

void imprimir_informacoes_produto(ARQUIVOS files, int codigo){
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    int pos = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);
    ARVOREB * r = ler_no(files.file_indices, pos);
    printf("\ncodigo: %d\n", r->chave[pos]);

    if(pos != -1) {
        ARVOREB * r = ler_no(files.file_indices, pos);
        DADOS_REGISTRO *informacoes_produto = ler_registro(files.file_dados, r->pt_dados[pos]);
        printf("Codigo: %d, Nome: %s\n", informacoes_produto->produto.codigo, informacoes_produto->produto.nome);
        free(informacoes_produto);
    } else {
        printf("Elemento nao encontrado!\n");
    }

    free(cab_indices);
}
