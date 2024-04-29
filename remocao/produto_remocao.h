//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "../produto/produto.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"

//void remover_produto(ARQUIVOS files);
//void remover_produto_file(ARQUIVOS files, int codigo);
//void left_shift(ARQUIVOS files, ARVOREB * no, int pos_no, int pos);
//void right_shift(ARQUIVOS files, ARVOREB * no, int pos_no, int pos);
//void concatenar_nos(ARQUIVOS files, ARVOREB * no, int pos_no, int pos);
//void ajustar_no(ARQUIVOS files, ARVOREB * no, int pos_no, int pos);
//void remover_valor(ARQUIVOS files, ARVOREB * no, int pos_no, int pos);
//void copiar_sucessor(ARQUIVOS files, ARVOREB * no, int pos_raiz, int pos);
//int remover_codigo_da_arvore(ARQUIVOS files, int codigo, ARVOREB * raiz, int pos_raiz);
//int mais_chaves_que_min(ARVOREB * r);
//int busca_pos_chave(ARVOREB * r, int codigo);
//void atualiza_lista_dados_livres(ARQUIVOS files, CABECALHO_DADOS * cab_dados, int pos_registro);
//void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo);
//void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
//int buscar_chave_sucessora_folha(ARQUIVOS files, ARVOREB * no_a_remover, int pos_codigo, int * pos_no_sucessor);
//int remover_caso2(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);
//int buscar_pai(ARQUIVOS files, int pos_raiz, int codigo, int * pos_filho_remocao);
//int pode_redistribuir(ARQUIVOS files, int pos_pai, int pos_filho_remocao, int * pegar_esq, int * pegar_dir);
//void redistribuir_partir_da_direita(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_dir);
//void redistribuir_partir_da_esquerda(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq);
//void redistribuir(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq, int pegar_dir);
//void buscar_filhos_esq_dir(ARQUIVOS files, int pos_pai, int pos_filho_remocao, int * pegar_esq, int * pegar_dir);
//void concatenar_esquerda(ARQUIVOS files, ARVOREB * pai, ARVOREB * esq, ARVOREB * no_a_remover, int pos_filho_remocao);
//void concatenar_direita(ARQUIVOS files, ARVOREB * pai, ARVOREB * dir, ARVOREB * no_a_remover, int pos_filho_remocao);
//void concatenar(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq, int pegar_dir);
//void verificar_redistribuicao_ou_concatenacao(ARQUIVOS files, int pos_raiz, ARVOREB * no_a_remover, int pos_pai, int pos_filho_remocao, int pos_remocao, int codigo);
//int equal(ARVOREB * raiz, ARVOREB * no_a_remover);
////int eh_raiz(ARQUIVOS files, ARVOREB * no_a_remover);
void remover_produto(ARQUIVOS files);
ARVOREB * encontrar_irmao_esq(FILE * file_indices, ARVOREB * filho);
ARVOREB * encontrar_irmao_dir(FILE* file_indices, ARVOREB * filho);
int pode_emprestar(ARVOREB * r);
int is_emprestimo(FILE* file_indices, ARVOREB * r);
void redistribuir_pela_esq(FILE* file_indices, ARVOREB * r, ARVOREB * esq);
void redistribuir_pela_dir(FILE* file_indices, ARVOREB * r, ARVOREB * dir);
void redistribuir(FILE* file_indices, ARVOREB * r);
void atualizar_pos_livres_indices(FILE *file_dados, int pos);
void atualizar_pos_livres_dados(FILE* file_dados, int pos);
void concatenar_pela_esq(FILE* file_indices, ARVOREB * r, ARVOREB * esq);
void concatenar_pela_dir(FILE* file_indices, ARVOREB * r, ARVOREB * dir);
void concatenar(FILE* file_indices, ARVOREB * r);
void balancear(FILE * file_indices, ARVOREB * r);
void mudar_raiz(FILE* file_indices, int raiz);
ARVOREB * remover(ARQUIVOS files, ARVOREB * r, int codigo);

#endif //PRODUTO_REMOCAO_H
