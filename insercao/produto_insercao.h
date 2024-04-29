//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_INSERCAO_H
#define PRODUTO_INSERCAO_H

#include "../produto/produto.h"
#include "../file/file.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../cabecalho/cabecalho_dados.h"

PRODUTO_DATA * ler_produto();
int overflow (ARVOREB * r);
void imprimir_produto(PRODUTO_DATA * produto);
ARVOREB * ler_no(FILE * file_indices, int pos);
void escreve_no(FILE * file_indices, ARVOREB * no, int pos);
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos);
void escreve_registro(FILE * file_dados, DADOS_REGISTRO * registro, int pos);
void imprimir_cabecalho_indices(CABECALHO_INDICES * cab);
void imprimir_cabecalho_dados(CABECALHO_DADOS * cab);
void cadastrar_produto(ARQUIVOS files);
void cria_no(ARVOREB * r, int codigo, int pos_dados);
void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto);
int split(ARQUIVOS files, ARVOREB * x, int pos, int * meio, int * pos_meio, CABECALHO_INDICES * cab_indices);
void cadastrar_produto_file(ARQUIVOS files, PRODUTO_DATA * produto);
int busca_pos(ARVOREB * r, int codigo, int * pos);
void adiciona_direita(ARVOREB * r, int pos, int codigo, int pt_dados, int p);
void cadastrar_aux(ARQUIVOS files, ARVOREB * r, int codigo, int pt_dados, int pos_atual, CABECALHO_INDICES * cab_indices);


#endif //PRODUTO_INSERCAO_H
