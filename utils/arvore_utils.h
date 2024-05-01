//
// Created by andre on 29/04/2024.
//

#ifndef TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
#define TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H

#include "../produto/produto.h"
#include "../file/file.h"

int vazia(ARVOREB * r);
int eh_folha(ARVOREB * r);
int eh_raiz(FILE * file_indices, ARVOREB * r);
int underflow(FILE * file_indices, ARVOREB * r);
int buscar_pos_chave(ARVOREB * r, int codigo);
int buscar_pos_filho(ARVOREB * r, int pos);
int mais_chaves_que_min(ARVOREB * r);
int buscar_no(FILE * file_indices, int codigo);
int buscar_no_aux(FILE * file_indices, int codigo, int pos);
int buscar_pai(FILE * file_indices, int codigo);
int buscar_pai_aux(FILE * file_indices, int pos_raiz, int codigo);
int buscar_pai_by_pos(FILE * file_indices, int pos_pai);
int buscar_pai_by_pos_aux(FILE * file_indices, int pos_raiz, int pos_pai);
int buscar_pos_chave_separadora(FILE* file_indices, ARVOREB * esq, ARVOREB * dir);

#endif //TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
