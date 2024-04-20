//
// Created by andre on 08/04/2024.
//

#ifndef FILE_H
#define FILE_H

#include "../cabecalho/cabecalho_dados.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../produto/produto.h"

// Definição da estrutura ARQUIVOS
typedef struct {
    FILE * file_indices;        // Ponteiro para o arquivo de cursos
    FILE * file_dados;   // Ponteiro para o arquivo de disciplinas
} ARQUIVOS;

void verificar_arquivos(ARQUIVOS * files);
void fechar_arquivos(ARQUIVOS * files);
int is_vazio(ARQUIVOS files, int get_file_indices);
int tem_indices_livres(ARQUIVOS files, int get_file_indices);
ARVOREB * ler_no(FILE * file_indices, int pos);
void escreve_no(FILE * file_indices, ARVOREB * no, int pos);
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos);
void escreve_registro(FILE * file_dados, DADOS_REGISTRO * registro, int pos);

#endif //FILE_H
