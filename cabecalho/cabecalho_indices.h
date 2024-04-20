//
// Created by andre on 08/04/2024.
//

#ifndef CABECALHO_INDICES_H
#define CABECALHO_INDICES_H

// Definição da estrutura do cabeçalho do arquivo de índices
typedef struct {
    int posRaiz; // Posição da riz da árvore
    int posTopo; // 1ª posição não usada no fim do arquivo
    int posLivre; // Posição do início da lista de nós livres
} CABECALHO_INDICES;

// Função para criar uma árvore nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void criaArvoreVaziaIndices(FILE * arq);

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_INDICES * lerCabecalhoIndices(FILE * arq);

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O cabeçalho é escrito no arquivo
void escreverCabecalhoIndices(FILE * arq, CABECALHO_INDICES * cab);

#endif //CABECALHO_INDICES_H
