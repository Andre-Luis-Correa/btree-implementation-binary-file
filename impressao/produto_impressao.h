//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_IMPRESSAO_H
#define PRODUTO_IMPRESSAO_H

#include "../produto/produto.h"
#include "../file/file.h"

#define TAMANHO_FILA 100 // Ajuste o tamanho conforme necess?rio

struct noLista
{
    int info;
    struct noLista* prox;
};

typedef struct noLista noL;

typedef struct noFila
{
    struct noLista* inicio;
    struct noLista* fim;
} Fila;

void imprimir_lista_produtos(ARQUIVOS files, int pos_atual);
void imprimir_lista_indices_livres(FILE * file_indices, int pos_atual);
void imprimir_lista_registros_livres(FILE * file_dados, int pos_atual);
void imprimir_informacoes_produto(ARQUIVOS files, int codido);
void imprimir_no(ARVOREB *r);
void imprimir_arvore(ARQUIVOS files);
void imprimir_info_nos_chaves(ARQUIVOS files, int pos);

#endif //PRODUTO_IMPRESSAO_H