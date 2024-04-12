//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "../produto/produto.h"

void remover_produto(ARQUIVOS files);
void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao);
int mais_chaves_que_min(ARVOREB * r);
int bus_pos_chave(ARVOREB * r, int codigo);
void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo);
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
#endif //PRODUTO_REMOCAO_H
