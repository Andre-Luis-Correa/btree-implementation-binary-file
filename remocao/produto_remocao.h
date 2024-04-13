//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "../produto/produto.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"

void remover_produto(ARQUIVOS files);
int mais_chaves_que_min(ARVOREB * r);
int busca_pos_chave(ARVOREB * r, int codigo);
void atualiza_lista_dados_livres(ARQUIVOS files, CABECALHO_DADOS * cab_dados, int pos_registro);
void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo);
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
int buscar_chave_sucessora_folha(ARQUIVOS files, ARVOREB * no_a_remover, int pos_codigo, int * pos_no_sucessor);
int remover_caso2(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao);
#endif //PRODUTO_REMOCAO_H
