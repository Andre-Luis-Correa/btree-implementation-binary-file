//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "cabecalho_dados.h"

// Função para criar uma lista nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void cria_arvore_vazia_dados(FILE * arq){
    CABECALHO_DADOS * cab = (CABECALHO_DADOS *) malloc(sizeof(CABECALHO_DADOS));
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho_dados(arq, cab);
    free(cab);
}

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_DADOS * le_cabecalho_dados(FILE * arq) {
    CABECALHO_DADOS * cab = (CABECALHO_DADOS *) malloc(sizeof(CABECALHO_DADOS));
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fread(cab, sizeof(CABECALHO_DADOS ), 1, arq);
    return cab;
}

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: O cabeçalho é escrito no arquivo
void escreve_cabecalho_dados(FILE* arq, CABECALHO_DADOS * cab){
    fseek(arq, 0, SEEK_SET); // Posiciona no início do arquivo
    fwrite(cab, sizeof(CABECALHO_DADOS), 1, arq);
}

void imprimir_cabecalho_dados(CABECALHO_DADOS * cab){
    printf("\nCABECALHO DE DADOS: topo: %d livre: %d\n", cab->pos_topo, cab->pos_livre);
}