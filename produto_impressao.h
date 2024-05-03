#ifndef PRODUTO_IMPRESSAO_H
#define PRODUTO_IMPRESSAO_H

#include "produto.h"
#include "file.h"

// Definição da estrutura de nó da lista encadeada
struct noLista {
    int info;              // Informação armazenada no nó
    struct noLista* prox;  // Ponteiro para o próximo nó na lista
};

// Definição de um alias para a estrutura de nó da lista encadeada
typedef struct noLista noL;

// Definição da estrutura de nó da fila, que utiliza a lista encadeada
typedef struct noFila {
    struct noLista* inicio;  // Ponteiro para o primeiro nó da fila
    struct noLista* fim;     // Ponteiro para o último nó da fila
} Fila;

// Função para imprimir a lista de produtos armazenados na árvore B-B
// Pré-condições: Todos os arquivos e nós devem estar acessíveis e corretamente inicializados.
//                A posição atual na árvore deve ser válida.
// Pós-condições: A lista de produtos é impressa na saída padrão, seguindo a estrutura definida.
void imprimir_lista_produtos(ARQUIVOS files, int pos_atual);

// Função para imprimir as informações de um produto específico na árvore B
// Pré-condições: Todos os arquivos e nós devem estar acessíveis e corretamente inicializados.
//                O código do produto a ser buscado deve ser válido e existir na árvore.
// Pós-condições: As informações do produto são impressas na saída padrão, seguindo a estrutura definida.
void imprimir_informacoes_produto(ARQUIVOS files, int codido);

// Função para imprimir a lista de índices livres no arquivo de índices
// Pré-condições: O arquivo de índices deve estar acessível e corretamente inicializado.
//                A posição atual na lista de índices livres deve ser válida.
// Pós-condições: A lista de posições livres no arquivo de índices é impressa na saída padrão.
void imprimir_lista_indices_livres(FILE * file_indices, int pos_atual);

// Função para imprimir a lista de registros livres no arquivo de dados
// Pré-condições: O arquivo de dados deve estar acessível e corretamente inicializado.
//                A posição atual na lista de registros livres deve ser válida.
// Pós-condições: A lista de posições livres no arquivo de dados é impressa na saída padrão.
void imprimir_lista_registros_livres(FILE * file_dados, int pos_atual);

// Função para buscar o nível de um determinado nó na árvore B-B
// Pré-condições: O arquivo de índices deve estar acessível e corretamente inicializado.
//                O nó e a chave a serem buscados devem ser válidos.
// Pós-condições: O nível do nó na árvore é retornado.
int buscaNivel(FILE* arq, ARVOREB* r, int chave, int count);

// Função para buscar um nó específico na árvore B
// Pré-condições: O arquivo de índices deve estar acessível e corretamente inicializado.
//                O nó e a chave a serem buscados devem ser válidos.
// Pós-condições: O nó contendo a chave é retornado, ou NULL se a chave não for encontrada.
ARVOREB * busca(FILE* arq, ARVOREB* r, int info, int * pos);

// Função para verificar se a fila está vazia
// Pré-condições: A fila deve estar corretamente inicializada.
// Pós-condições: Retorna 1 se a fila estiver vazia, caso contrário retorna 0.
int vaziaFila(Fila* f);

// Função para enfileirar um elemento na fila
// Pré-condições: A fila deve estar corretamente inicializada.
// Pós-condições: O elemento é enfileirado na fila.
void enqueue(Fila* f, int x);

// Função para enfileirar os filhos de um nó na fila
// Pré-condições: O arquivo de índices e o nó devem estar acessíveis e corretamente inicializados.
//                A fila deve estar corretamente inicializada.
// Pós-condições: Os filhos do nó são enfileirados na fila.
void enfileiraFilhos(FILE* arq, ARVOREB* r, Fila* f);

// Função para desenfileirar um elemento da fila
// Pré-condições: A fila deve estar corretamente inicializada e não vazia.
// Pós-condições: O elemento é desenfileirado da fila e retornado.
int * dequeue(Fila* f);

// Função para criar uma fila vazia
// Pré-condições: Nenhuma.
// Pós-condições: Retorna a fila vazia.
Fila * cria_fila_vazia();

// Função para imprimir a árvore B-B por níveis
// Pré-condições: Todos os arquivos e nós devem estar acessíveis e corretamente inicializados.
//                O nó raiz da árvore deve ser válido.
// Pós-condições: A árvore B-B é impressa por níveis na saída padrão.
void imprimir_por_niveis(ARQUIVOS files, ARVOREB* r);

// Função para imprimir a árvore B-B
// Pré-condições: O arquivo de índices deve estar acessível e corretamente inicializado.
// Pós-condições: A árvore B-B é impressa na saída padrão.
void imprimir_arvore(ARQUIVOS files);

#endif //PRODUTO_IMPRESSAO_H