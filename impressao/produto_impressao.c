//
// Created by andre on 08/04/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "produto_impressao.h"
#include "../insercao/produto_insercao.h"
#include "../file/file.h"

void imprimir_lista_produtos(ARQUIVOS files, int pos_atual) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos_atual == -1) {
        free(cab_indices);
        return;
    }else{
        ARVOREB *no = ler_no(files.file_indices, pos_atual);

        for (int i = 0; i <= no->num_chaves; i++) {
            imprimir_lista_produtos(files, no->filho[i]);

            if (i != no->num_chaves) {
                DADOS_REGISTRO *registro = ler_registro(files.file_dados, no->pt_dados[i]);
                printf("Codigo: %d \n Nome: %s \n Marca: %s \n Preco: %f \n", registro->produto.codigo, registro->produto.nome, registro->produto.marca, registro->produto.preco);
                printf("\n");
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

    if(pos != -1) {
        ARVOREB * r = ler_no(files.file_indices, pos);

        int i;
        for(i = 0; i < r->num_chaves; i++){
            if(r->chave[i] == codigo) break;
        }

        DADOS_REGISTRO *informacoes_produto = ler_registro(files.file_dados, r->pt_dados[i]);
        printf("Codigo: %d \n Nome: %s \n Marca: %s \n Preco: %f \n", informacoes_produto->produto.codigo, informacoes_produto->produto.nome, informacoes_produto->produto.marca, informacoes_produto->produto.preco);
        free(informacoes_produto);
    } else {
        printf("Elemento nao encontrado!\n");
    }

    free(cab_indices);
}


// Função para inicializar a fila
void inicializar_fila(Fila *fila) {
    fila->frente = 0;
    fila->tras = 0;
}

// Função para enfileirar um nó
void enfileirar(Fila *fila, ARVOREB *no) {
    if (fila->tras < TAMANHO_FILA) {
        fila->elementos[fila->tras++] = no;
    } else {
        printf("Fila cheia! Não é possível enfileirar.\n");
    }
}

// Função para desenfileirar um nó
ARVOREB *desenfileirar(Fila *fila) {
    if (fila->frente < fila->tras) {
        return fila->elementos[fila->frente++];
    } else {
        printf("Fila vazia! Não é possível desenfileirar.\n");
        return NULL;
    }
}

// Função para verificar se a fila está vazia
int fila_vazia(Fila *fila) {
    return fila->frente == fila->tras;
}
void imprimir_por_niveis(ARQUIVOS files, int pos_raiz) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos_raiz == -1) {
        printf("Árvore vazia.\n");
        free(cab_indices);
        return;
    }

    int nivel_atual = 1;
    int nivel_proximo = 0;

    ARVOREB *fila[100]; // Tamanho da fila ajustável conforme necessário
    int frente = 0;
    int tras = 0;

    fila[tras++] = ler_no(files.file_indices, pos_raiz);

    while (frente != tras) {
        ARVOREB *no_atual = fila[frente++];
        nivel_atual--;

        for (int i = 0; i < no_atual->num_chaves; i++) {
            printf("%d", no_atual->chave[i]);
            if (i < no_atual->num_chaves - 1) {
                printf(",");
            }
        }

        printf("|"); // Divisor de nó

        if (no_atual->filho[0] != -1) {
            for (int i = 0; i <= no_atual->num_chaves; i++) {
                fila[tras++] = ler_no(files.file_indices, no_atual->filho[i]);
                nivel_proximo++;
            }
        }

        if (nivel_atual == 0) {
            printf("\n");
            nivel_atual = nivel_proximo;
            nivel_proximo = 0;
        }
    }

    free(cab_indices);
    // Liberar os nós da fila
    for (int i = 0; i < tras; i++) {
        free(fila[i]);
    }
}

void imprimir_arvore(ARQUIVOS files) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);
    int pos =  cab_indices->pos_raiz;
    if (pos == -1) {
        free(cab_indices);
        return;
    } else {
        ARVOREB *no = ler_no(files.file_indices, pos);
        printf("imprimindo arvoreee :\n\n");
        imprimir_por_niveis(files, no);
    }
}
void imprimir_no(ARVOREB *r) {
    printf("\n-----------------------------\n");
    printf("    O no analisado foi: \n");

    printf("Chaves: ");
    for(int i = 0; i < r->num_chaves; i++){
        printf("%d ", r->chave[i]);
    }
    printf("\n");
    printf("Pt. Dados: ");
    for(int i = 0; i < r->num_chaves; i++){
        printf("%d ", r->pt_dados[i]);
    }
    printf("\n");
    printf("Filhos: ");
    for(int i = 0; i <= r->num_chaves; i++){
        printf("%d ", r->filho[i]);
    }
    printf("\n-----------------------------\n");
}


void imprimir_info_nos_chaves(ARQUIVOS files, int pos){
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos == -1) {
        //printf("Arvore vazia!\n");
        free(cab_indices);
        return;
    }else{
        ARVOREB * no = ler_no(files.file_indices, pos);
        imprimir_no(no);

        for(int i = 0; i <= no->num_chaves; i++){
            imprimir_info_nos_chaves(files, no->filho[i]);
        }

        free(no);
        free(cab_indices);
    }
}
