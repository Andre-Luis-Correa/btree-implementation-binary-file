//
// Created by andre on 08/04/2024.
//

#ifndef CABECALHO_DADOS_H
#define CABECALHO_DADOS_H

// Definição da estrutura do cabeçalho do arquivo de dados
typedef struct {
    int pos_topo; // 1.ª posição não usada no fim do arquivo
    int pos_livre; // Posição do início da lista de nós livres
} CABECALHO_DADOS;

// Função para criar uma árvore nova em arquivo
// Pré-condição: O arquivo deve estar aberto para leitura/escrita
// Pós-condição: O arquivo é inicializado com uma árvore vazia
void cria_arvore_vazia_dados(FILE * arq);

// Função para ler o cabeçalho do arquivo contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista
// Pós-condição: Retorna o ponteiro para o cabeçalho lido
CABECALHO_DADOS * le_cabecalho_dados(FILE * arq);

// Função para escrever no arquivo o cabeçalho contendo as informações da árvore
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O cabeçalho é escrito no arquivo
void escreve_cabecalho_dados(FILE* arq, CABECALHO_DADOS * cab);

#endif //CABECALHO_DADOS_H
