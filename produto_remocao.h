#ifndef PRODUTO_REMOCAO_H
#define PRODUTO_REMOCAO_H

#include "produto.h"
#include "produto_insercao.h"
#include "produto_impressao.h"

// Função para remover um produto da árvore B
// Pré-condições: ARQUIVOS files contém os arquivos necessários para operações de leitura e escrita,
//                 incluindo os arquivos de índices e de dados.
// Pós-condições: O produto com o código especificado é removido da árvore B, se presente. Caso contrário,
//                 mensagens apropriadas são exibidas.
void remover_produto(ARQUIVOS files);

// Função para atualizar a lista de posições livres no arquivo de dados após a remoção de um registro
// Pré-condições: O arquivo de dados deve estar aberto e a posição do registro removido deve ser válida.
// Pós-condições: A lista de posições livres no arquivo de dados é atualizada.
void atualizar_pos_livres_dados(FILE * file_dados, int pos);

// Função para atualizar a lista de posições livres no arquivo de índices após a remoção de um nó
// Pré-condições: O arquivo de índices deve estar aberto e a posição do nó removido deve ser válida.
// Pós-condições: A lista de posições livres no arquivo de índices é atualizada.
void atualizar_pos_livres_indices(FILE * file_indices, int pos);

// Função para atualizar um nó após a remoção de um registro em um nó folha
// Pré-condições: O arquivo de índices deve estar aberto e o nó folha, bem como as posições de remoção e código, devem ser válidos.
// Pós-condições: O nó é atualizado com as informações da remoção.
void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo);

// Função para tratar a remoção quando esta é feita em um nó folha com número de chaves maior que o mínimo (ORDEM/2 + ORDEM%2 - 1)
// Pré-condições: O arquivo de índices deve estar aberto e o nó a ser removido, bem como o código e a posição de remoção, devem ser válidos.
// Pós-condições: A remoção é tratada de acordo com o caso específico.
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);

// Função para buscar a chave sucessora em um nó folha
// Pré-condições: O arquivo de índices deve estar aberto e o nó a ser removido, bem como a posição da chave e a posição do nó sucessor, devem ser válidos.
// Pós-condições: A chave sucessora é retornada e a posição do nó sucessor é atualizada.
int buscar_chave_sucessora_folha(ARQUIVOS files, ARVOREB * no_a_remover, int pos_codigo, int * pos_no_sucessor);

// Função para tratar a remoção quando esta é feita em um nó interno
// Pré-condições: O arquivo de índices deve estar aberto e o nó a ser removido, bem como o código e a posição de remoção, devem ser válidos.
// Pós-condições: A remoção é tratada de acordo com o caso específico.
int remover_caso2(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao);

// Função para verificar se é possível realizar a redistribuição de chaves entre irmãos
// Pré-condições: O arquivo de índices deve estar aberto, a posição do pai, o índice do filho, bem como os ponteiros para as posições dos filhos esquerdo e direito, devem ser válidos.
// Pós-condições: Retorna 1 se a redistribuição for possível, caso contrário, retorna 0.
int pode_redistribuir(ARQUIVOS files, int pos_pai, int indice_filho, int * pegar_esq, int * pegar_dir);

// Função para redistribuir chaves a partir do irmão direito
// Pré-condições: O arquivo de índices deve estar aberto e as posições do pai, remoção, filho da remoção e irmão direito devem ser válidos.
// Pós-condições: As chaves são redistribuídas entre o nó e seu irmão direito.
void redistribuir_partir_da_direita(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_dir);

// Função para redistribuir chaves a partir do irmão esquerdo
// Pré-condições: O arquivo de índices deve estar aberto e as posições do pai, remoção, filho da remoção e irmão esquerdo devem ser válidos.
// Pós-condições: As chaves são redistribuídas entre o nó e seu irmão esquerdo.
void redistribuir_partir_da_esquerda(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_esq);

// Função para realizar a redistribuição de chaves entre irmãos
// Pré-condições: O arquivo de índices deve estar aberto e as posições do pai, remoção, filho da remoção e irmãos devem ser válidos.
// Pós-condições: As chaves são redistribuídas entre os irmãos conforme necessário.
void redistribuir(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pos_esq, int pos_dir);

// Função para buscar os filhos esquerdo e direito de um nó pai
// Pré-condições: O arquivo de índices deve estar aberto e acessível. A posição do nó pai deve ser válida.
// Pós-condições: As posições dos filhos esquerdo e direito são retornadas por meio dos parâmetros pos_esq e pos_dir, respectivamente.
void buscar_filhos_esq_dir(ARQUIVOS files, int pos_pai, int indice_remocao, int * pos_esq, int * pos_dir);

// Função para concatenar o nó da esquerda com o nó a ser removido
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                O nó a ser removido não deve ser a raiz e deve conter as chaves a serem concatenadas.
// Pós-condições: O nó da esquerda é concatenado com o nó a ser removido, mantendo a estrutura da árvore B.
void concatenar_esquerda(ARQUIVOS files, ARVOREB * pai, ARVOREB * esq, ARVOREB * no_a_remover, int indice_filho);

// Função para concatenar o nó da direita com o nó a ser removido
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                O nó a ser removido não deve ser a raiz e deve conter as chaves a serem concatenadas.
// Pós-condições: O nó da direita é concatenado com o nó a ser removido, mantendo a estrutura da árvore B.
void concatenar_direita(ARQUIVOS files, ARVOREB * pai, ARVOREB * dir, ARVOREB * no_a_remover, int pos_filho_remocao);

// Função para realizar a concatenação dos nós
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                As posições dos nós pai, remoção, filhos esquerdo e direito devem ser válidas.
// Pós-condições: Os nós são concatenados conforme necessário, mantendo a estrutura da árvore B.
void concatenar(ARQUIVOS files, int pos_pai, int pos_remocao, int indice_filho, int pos_esq, int pos_dir);

// Função para balancear a árvore após uma remoção
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                A posição do pai, índice do filho removido e posição da remoção devem ser válidos.
// Pós-condições: A árvore é balanceada de acordo com as regras da árvore B.
void balancear(ARQUIVOS files, int pos_pai, int indice_filho, int pos_remocao);

// Função para verificar e atualizar o pai após uma remoção.
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                A posição do pai a ser verificado deve ser válida.
// Pós-condições: O pai é atualizado conforme necessário, mantendo a integridade da árvore B.
void verificar_pai(ARQUIVOS files, int pos_pai);

// Função para remover uma chave da árvore B-B
// Pré-condições: Todos os nós e arquivos devem estar acessíveis e corretamente inicializados.
//                O código da chave a ser removida, a posição da raiz e a posição de remoção devem ser válidos.
// Pós-condições: A chave é removida da árvore B-B, mantendo sua estrutura e integridade.
void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao);

#endif //PRODUTO_REMOCAO_H
