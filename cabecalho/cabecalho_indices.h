//
// Created by andre on 08/04/2024.
//

#ifndef CABECALHO_INDICES_H
#define CABECALHO_INDICES_H

// Definição da estrutura do cabeçalho do arquivo de índices
typedef struct {
    int pos_raiz; // Posição da riz da árvore
    int pos_topo; // 1ª posição não usada no fim do arquivo
    int pos_livre; // Posição do início da lista de nós livres
} CABECALHO_INDICES;

// Função para criar uma árvore nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void cria_arvore_vazia_indices(FILE * arq);

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_INDICES * le_cabecalho_indices(FILE * arq);

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O cabeçalho é escrito no arquivo
void escreve_cabecalho_indices(FILE * arq, CABECALHO_INDICES * cab);

#endif //CABECALHO_INDICES_H
