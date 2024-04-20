#ifndef PRODUTO_H
#define PRODUTO_H

#define ORDEM 3
#define MAX_NOME 50
#define MAX_MARCA 30
#define MAX_CATEGORIA 50

#include "../file/file.h"

// Estrutura para nó da árvore B*
typedef struct indice_node {
    int chave[ORDEM];   // Chaves
    int pt_dados[ORDEM]; // Posições dos registros de dados no arquivo
    int filho[ORDEM+1]; // Ponteiros para os filhos
    int num_chaves;     // Número de chaves presentes no nó
    int prox_livre;     // Posição do próximo registro livre
} ARVOREB;

// Estrutura para os dados do produto
typedef struct produto_data {
    int codigo;
    char nome[MAX_NOME + 1];      // Nome do produto
    char marca[MAX_MARCA + 1];    // Marca do produto
    char categoria[MAX_CATEGORIA + 1]; // Categoria do produto
    int estoque;                  // Quantidade em estoque
    float preco;                  // Preço do produto
} PRODUTO_DATA;

// Estrutura para registro de dados
typedef struct dados_registro {
    PRODUTO_DATA produto; // Dados do produto
    int prox_livre;       // Encadeamento para registro livre
} DADOS_REGISTRO;

#endif //PRODUTO_H
