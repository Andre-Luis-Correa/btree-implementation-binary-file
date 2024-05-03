//
// Created by andre on 29/04/2024.
//

#ifndef TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
#define TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H

#include "produto.h"
#include "file.h"

// Verifica se uma árvore B está vazia
// Pré-condição: nenhuma
// Pós-condição: retorna 1 se a árvore estiver vazia, 0 caso contrário
int vazia(ARVOREB * r);

// Verifica se um nó da árvore B é folha
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o nó for uma folha, 0 caso contrário
int eh_folha(ARVOREB * r);

// Verifica se um nó é a raiz da árvore B
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó deve ser válida
// Pós-condição: retorna 1 se o nó for a raiz, 0 caso contrário
int eh_raiz(FILE * file_indices, int pos);

// Busca a posição de uma chave em um nó da árvore B
// Pré-condição: o nó deve existir
// Pós-condição: retorna a posição da chave se encontrada, -1 caso contrário
int buscar_pos_chave(ARVOREB * r, int codigo);

// Busca a posição de um filho em um nó da árvore B
// Pré-condição: o nó deve existir
// Pós-condição: retorna a posição do filho se encontrado, -1 caso contrário
int buscar_pos_filho(ARVOREB * r, int pos);

// Verifica se um nó possui mais chaves que o mínimo exigido
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o número de chaves for maior que o mínimo, 0 caso contrário
int mais_chaves_que_min(ARVOREB * r);

// Função para buscar um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do nó se encontrado, -1 caso contrário
int buscar_no(FILE * file_indices, int codigo);

// Função auxiliar para buscar um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do nó se encontrado, -1 caso contrário
int buscar_no_aux(FILE * file_indices, int codigo, int pos);

// Função para buscar o pai de um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai(FILE * file_indices, int codigo);

// Função auxiliar para buscar o pai de um nó na árvore B a partir de um código de produto
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_aux(FILE * file_indices, int pos_raiz, int codigo);

// Função para buscar o pai de um nó na árvore B a partir de uma posição de nó
// Pré-condição: o arquivo de índices deve ser válido
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_by_pos(FILE * file_indices, int pos_pai);

// Função auxiliar para buscar o pai de um nó na árvore B a partir de uma posição de nó
// Pré-condição: o arquivo de índices deve ser válido e a posição do nó atual deve ser válida
// Pós-condição: retorna a posição do pai se encontrado, -1 caso contrário
int buscar_pai_by_pos_aux(FILE * file_indices, int pos_raiz, int pos_pai);

#endif //TRABALHO_AED_3_BRUNA_ANDRE_ARVORE_UTILS_H
