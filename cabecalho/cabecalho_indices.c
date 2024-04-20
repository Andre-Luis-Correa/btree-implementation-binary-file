//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "cabecalho_indices.h"

// Função para criar uma lista nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void cria_arvore_vazia_indices(FILE* arq){
    CABECALHO_INDICES * cab = (CABECALHO_INDICES*) malloc(sizeof(CABECALHO_INDICES));
    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho_indices(arq, cab);
    free(cab);
}

// Função para verificar se a árvore está vazia
// Pré-condição: O ponteiro para o cabeçalho deve ser válido
// Pós-condição: Retorna 1 se a árvore está vazia, 0 caso contrário
int is_vazia_arvore_indices(CABECALHO_INDICES * cab){
    return (cab->pos_raiz == -1);
}

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_INDICES * le_cabecalho_indices(FILE * arq) {
    CABECALHO_INDICES * cab = (CABECALHO_INDICES*) malloc(sizeof(CABECALHO_INDICES));
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fread(cab, sizeof(CABECALHO_INDICES), 1, arq);
    return cab;
}

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: O cabeçalho é escrito no arquivo
void escreve_cabecalho_indices(FILE* arq, CABECALHO_INDICES* cab){
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fwrite(cab, sizeof(CABECALHO_INDICES), 1, arq);
}

void imprimir_cabecalho_indices(CABECALHO_INDICES * cab){
    printf("\nCABECALHO DE INDICES: raiz: %d topo: %d livre: %d\n", cab->pos_raiz, cab->pos_topo, cab->pos_livre);
}