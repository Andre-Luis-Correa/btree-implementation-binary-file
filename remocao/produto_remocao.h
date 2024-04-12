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
int pode_emprestar(ARVOREB * r);
ARVOREB *find_irmao_esq(FILE * file_indices, ARVOREB * r);
ARVOREB *find_irmao_dir(FILE * file_indices, ARVOREB * r);
int is_emprestimo(FILE* file_indices, ARVOREB * r);
void realizar_balanceamento(ARQUIVOS files, ARVOREB * r);
void remover(ARQUIVOS files, int pos_raiz, int pos_esq, int pos_dir, int codigo);

#endif //PRODUTO_REMOCAO_H
