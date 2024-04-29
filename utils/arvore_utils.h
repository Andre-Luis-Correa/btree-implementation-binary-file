//
// Created by andre on 29/04/2024.
//

#ifndef TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
#define TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H

#include "../produto/produto.h"
#include "../file/file.h"

int vazia(ARVOREB * r);
int eh_folha(ARVOREB * r);
int eh_raiz(ARVOREB * r);
int underflow(ARVOREB * r);
int busca_pos_chave(ARVOREB * r, int codigo);
int buscar_pai(FILE * file_indices, int codigo);
int buscar_pai_aux(FILE * file_indices, int pos_raiz, int codigo);

#endif //TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
