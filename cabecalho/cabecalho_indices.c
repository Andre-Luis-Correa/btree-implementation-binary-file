//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "cabecalho_indices.h"

// Função para criar uma lista nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void criaArvoreVaziaIndices(FILE* arq){
    CABECALHO_INDICES * cab = (CABECALHO_INDICES*) malloc(sizeof(CABECALHO_INDICES));
    cab->posRaiz = -1;
    cab->posTopo = 0;
    cab->posLivre = -1;
    escreverCabecalhoIndices(arq, cab);
    free(cab);
}

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_INDICES * lerCabecalhoIndices(FILE * arq) {
    CABECALHO_INDICES * cab = (CABECALHO_INDICES*) malloc(sizeof(CABECALHO_INDICES));
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fread(cab, sizeof(CABECALHO_INDICES), 1, arq);
    return cab;
}

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: O cabeçalho é escrito no arquivo
void escreverCabecalhoIndices(FILE* arq, CABECALHO_INDICES* cab){
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fwrite(cab, sizeof(CABECALHO_INDICES), 1, arq);
}