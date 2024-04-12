//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_IMPRESSAO_H
#define PRODUTO_IMPRESSAO_H

#include "../produto/produto.h"

void imprimir_lista_produtos(ARQUIVOS files, int pos_atual);
void imprimir_informacoes_produto(ARQUIVOS files, int codido);
void imprimir_no(ARVOREB *r);
void imprimir_info_nos_chaves(ARQUIVOS files, int pos);

#endif //PRODUTO_IMPRESSAO_H