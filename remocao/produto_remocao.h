//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "../produto/produto.h"

int vazia(ARVOREB * r);
int eh_raiz(ARVOREB * r);
int underflow(ARVOREB * r);
void remover_produto(ARQUIVOS files);
ARVOREB * remover(ARQUIVOS files, ARVOREB * r, int codigo);

#endif //PRODUTO_REMOCAO_H
