//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_INSERCAO_H
#define PRODUTO_INSERCAO_H

#include "../produto/produto.h"

// Função para ler os dados de um produto
PRODUTO_DATA * ler_produto();

// Função para imprimir os dados de um produto
void imprimir_produto(PRODUTO_DATA * produto);

void cadastrar_produto_files(ARQUIVOS files, PRODUTO_DATA *pData);

// Função para cadastrar um produto sem nós livres
void cadastrar_produto_sem_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos);

// Função para cadastrar um produto sem nós livres
void cadastrar_produto_com_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos);

// Função para cadastrar um produto
void cadastrar_produto(ARQUIVOS files);

void cria_no(ARVOREB * r, int codigo, int pos_dados);

void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto);

void cadastrar_aux(ARQUIVOS files, ARVOREB * r, int codigo, int pt_dados, int pos_atual);

int busca_pos (ARVOREB * r, int codigo, int * pos);

void adiciona_direita (ARVOREB * r, int pos, int codigo, int pt_dados, int p);

int overflow (ARVOREB * r);

int split (ARQUIVOS files, ARVOREB * x, int pos, int * m, int * pos_meio);

#endif //PRODUTO_INSERCAO_H
