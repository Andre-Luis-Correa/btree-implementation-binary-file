//
// Created by andre on 09/04/2024.
//

#ifndef TRABALHO_AED_3_BRUNA_ANDRE_PRODUTO_INSERCAO_H
#define TRABALHO_AED_3_BRUNA_ANDRE_PRODUTO_INSERCAO_H

#include "../produto/produto.h"

// Função para ler os dados de um produto
PRODUTO_DATA ler_produto();

// Função para imprimir os dados de um produto
void imprimir_produto(PRODUTO_DATA produto);

// Função para cadastrar um produto sem nós livres
void cadastrar_produto_sem_nos_livres(ARQUIVOS files);

// Função para cadastrar um produto sem nós livres
void cadastrar_produto_com_nos_livres(ARQUIVOS files);

// Função para cadastrar um produto
void cadastrar_produto(ARQUIVOS files);

#endif //TRABALHO_AED_3_BRUNA_ANDRE_PRODUTO_INSERCAO_H
