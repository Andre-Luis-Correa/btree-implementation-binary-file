//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "../produto/produto.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"

void remover_produto(ARQUIVOS files);
void atualizar_pos_livres_dados(FILE * file_dados, int pos);
void atualizar_pos_livres_indices(FILE * file_indices, int pos);
void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo);
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
int buscar_chave_sucessora_folha(ARQUIVOS files, ARVOREB * no_a_remover, int pos_codigo, int * pos_no_sucessor);
int remover_caso2(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
int pode_redistribuir(ARQUIVOS files, int pos_pai, int indice_filho, int * pegar_esq, int * pegar_dir);
void redistribuir_partir_da_direita(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_dir);
void redistribuir_partir_da_esquerda(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_esq);
void redistribuir(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_esq, int pos_dir);
void buscar_filhos_esq_dir(ARQUIVOS files, int pos_pai, int indice_remocao, int * pos_esq, int * pos_dir);
void concatenar_esquerda(ARQUIVOS files, ARVOREB * pai, ARVOREB * esq, ARVOREB * no_a_remover, int indice_filho);
void concatenar_direita(ARQUIVOS files, ARVOREB * pai, ARVOREB * dir, ARVOREB * no_a_remover, int pos_filho_remocao);
void concatenar(ARQUIVOS files, int pos_pai, int pos_remocao, int indice_filho, int pos_esq, int pos_dir);
void balancear(ARQUIVOS files, int pos_pai, int indice_filho, int pos_remocao);
void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao);

#endif //PRODUTO_REMOCAO_H
