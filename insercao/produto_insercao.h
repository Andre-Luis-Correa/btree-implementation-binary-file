//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_INSERCAO_H
#define PRODUTO_INSERCAO_H

#include "../produto/produto.h"
#include "../file/file.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../cabecalho/cabecalho_dados.h"

// Função para ler os dados de um produto
// Pré-condição: nenhuma
// Pós-condição: retorna um ponteiro para a estrutura PRODUTO_DATA preenchida com os dados inseridos pelo usuário
PRODUTO_DATA * ler_produto();

// Verifica se um nó da árvore B está em overflow
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o número de chaves for igual à ordem da árvore, 0 caso contrário
int overflow (ARVOREB * r);

// Função para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices deve existir e estar aberto para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
void cadastrar_produto(ARQUIVOS files);

// Cria um novo nó na árvore B
// Pré-condição: nenhuma
// Pós-condição: o nó é criado com as informações passadas por parâmetro
void cria_no(ARVOREB * r, int codigo, int pos_dados);

// Cria um novo registro com os dados de um produto
// Pré-condição: nenhuma
// Pós-condição: o registro é criado com os dados do produto
void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto);

// Função para dividir um nó da árvore B em dois
// Pré-condição: o nó x deve existir e não estar vazio
// Pós-condição: divide o nó x em dois nós, retornando a posição do novo nó criado
int split(ARQUIVOS files, ARVOREB * x, int pos, int * meio, int * pos_meio, CABECALHO_INDICES * cab_indices);

// Obtém a próxima posição livre no arquivo de dados
// Pré-condição: o arquivo de dados deve estar aberto para leitura e escrita
// Pós-condição: retorna a próxima posição livre no arquivo de dados
int get_pos_livre_dados(FILE * file, CABECALHO_DADOS * cab);

// Obtém a próxima posição livre no arquivo de índices
// Pré-condição: o arquivo de índices deve estar aberto para leitura e escrita
// Pós-condição: retorna a próxima posição livre no arquivo de índices
int get_pos_livre_indices(FILE * file, CABECALHO_INDICES * cab);

// Função principal para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices e o arquivo de dados devem existir e estar abertos para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
void cadastrar_produto_file(ARQUIVOS files, PRODUTO_DATA * produto);

// Função para encontrar a posição onde uma chave deve ser inserida em um nó da árvore B
// Pré-condição: o nó r deve existir e não estar vazio
// Pós-condição: retorna 1 se a chave já existe no nó, caso contrário retorna 0 e atualiza a posição onde a chave deve ser inserida
int busca_pos(ARVOREB * r, int codigo, int * pos);

// Função para adicionar uma chave e seu ponteiro de dados à direita de uma posição específica em um nó da árvore B
// Pré-condição: o nó r deve existir e não estar cheio
// Pós-condição: a chave e seu ponteiro de dados são inseridos na posição especificada
void adiciona_direita(ARVOREB * r, int pos, int codigo, int pt_dados, int p);

// Função auxiliar para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices deve existir e estar aberto para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
void cadastrar_aux(ARQUIVOS files, ARVOREB * r, int codigo, int pt_dados, int pos_atual, CABECALHO_INDICES * cab_indices);


#endif //PRODUTO_INSERCAO_H
