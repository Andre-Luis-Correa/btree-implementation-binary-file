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
    FILE * fileIndices;        // Ponteiro para o arquivo de cursos
    FILE * fileRegistros;   // Ponteiro para o arquivo de disciplinas
} ARQUIVOS;

void verificarArquivos(ARQUIVOS * files);
void fecharArquivos(ARQUIVOS * files);
int isVazio(ARQUIVOS files, int getFileIndices);
int temPosLivre(ARQUIVOS files, int getFileIndices);
ARVOREB * lerNo(FILE * fileIndices, int pos);
void escreveNo(FILE * fileIndices, ARVOREB * no, int pos);
PRODUTO_REGISTRO * lerRegistro(FILE * fileDados, int pos);
void escreveRegistro(FILE * fileDados, PRODUTO_REGISTRO * registro, int pos);

#endif //FILE_H
