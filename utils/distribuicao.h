#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H
#include "disciplina.h"
#include "file.h"
#include "curso.h"
#include "disciplina.h"
#include "professor.h"

#define MAXKEY 10

// Estrutura que representa uma distribuição.
typedef struct {
    char cod_distribuicao[MAXKEY];  // Código único da distribuição.
    int cod_disciplina;  // Código da disciplina associada à distribuição.
    char ano_letivo[5];  // Ano letivo ao qual a distribuição está relacionada.
    int cod_professor;  // Código do professor responsável pela disciplina na distribuição.
} DISTRIBUICAO;

// Estrutura de nó para a árvore de distribuições.
typedef struct {
    DISTRIBUICAO distribuicao;  // Informações da distribuição.
    int esq;  // Índice do nó à esquerda na árvore.
    int dir;  // Índice do nó à direita na árvore.
} NO_DISTRIBUICAO;

// Função para ler os dados de uma distribuição do usuário.
// Pré-condição: Nenhuma.
// Pós-condição: Retorna uma distribuição lida do usuário.
DISTRIBUICAO ler_distribuicao();

// Lê um nó da distribuição do arquivo binário.
// Pré-condição: O arquivo de distribuição deve estar aberto e ser um arquivo binário válido.
//               A posição (pos) deve ser uma posição válida no arquivo.
// Pós-condição: Retorna um ponteiro para um novo nó lido do arquivo na posição especificada.
NO_DISTRIBUICAO * le_no_distribuicao (FILE * file_distribuicao, int pos);

// Função para buscar uma distribuição no arquivo com base na chave.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Retorna a posição no arquivo onde a distribuição com a chave foi encontrada.
int buscar_distribuicao(FILE *file_distribuicao, char chave[MAXKEY], int pos);

// Função para formatar o código da distribuição.
// Pré-condição: Nenhuma.
// Pós-condição: O parâmetro 'codigo' é preenchido com o código formatado.
void formatar_codigo(int codigo_disciplina, char ano_letivo[10], char codigo[10]);

// Função para inserir uma distribuição.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere uma nova distribuição no arquivo.
void inserir_distribuicao(FILE *file_distribuicao);

// Função para inserir uma distribuição proveniente do arquivo lote txt no arquivo binário.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere uma nova distribuição no arquivo.
void inserir_distribuicao_do_lote(FILE* file_distribuicao, DISTRIBUICAO distribuicao);

// Função para inserir uma distribuição no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo de distribuições.
void inserir_distribuicao_file(FILE *file_distribuicao, NO_DISTRIBUICAO *no_distribuicao);

// Função para escrever um nó no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Escreve o nó no arquivo de distribuições na posição especificada.
void escreve_no_distribuicao(FILE *file_distribuicao, NO_DISTRIBUICAO *no_distribuicao, int pos);

// Função para inserir um nó sem considerar nós livres.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo sem considerar nós livres.
void inserir_sem_nos_livres(FILE *file_distribuicao, NO_DISTRIBUICAO *no_distribuicao, int pos);

// Função para inserir um nó considerando nós livres.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo considerando nós livres.
void inserir_com_nos_livres(FILE *file_distribuicao, NO_DISTRIBUICAO *no_distribuicao, int pos);

// Função para imprimir as informações de uma distribuição.
// Pré-condição: Nenhuma.
// Pós-condição: Imprime as informações do nó de distribuição.
void imprimir_info_distribuicao(ARQUIVOS files, NO_DISTRIBUICAO * no_distribuicao);

// Função para imprimir as distribuições em ordem no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime as distribuições do arquivo em ordem a partir da posição especificada.
void imprimir_in_order_distribuicao(ARQUIVOS files, FILE* file_distribuicao, int pos_atual);

// Função para imprimir a lista de distribuições no arquivo.
// Pré-condição: Os arquivos no struct ARQUIVOS devem estar abertos.
// Pós-condição: Imprime a lista de distribuições do arquivo.
void imprimir_lista_distribuicao(ARQUIVOS files);

// Função para imprimir a lista de posições livres no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime a lista de posições livres no arquivo a partir da posição especificada.
void imprimir_posicoes_livres(FILE *file_distribuicao, int pos_atual);

// Função para imprimir a lista de posições livres no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime a lista de posições livres no arquivo.
void imprimir_posicoes_livres_wrapper(FILE *file_distribuicao);

// Função para remover uma distribuição.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Remove uma distribuição do arquivo.
void retira_distribuicao(FILE *file_distribuicao);

// Função para troca de distribuições
// Pré-condição: O arquivo file_distribuicao deve estar aberto, pos_destino e pos_origem devem ser posiçoes validas no arquivo
// Pós-condição: Troca as informações entre dois nós no arquivo.
void trocar_info(FILE *file_distribuicao, int pos_destino, int pos_origem);

// Função para remover um nó do arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Remove um nó do arquivo e retorna a nova posição do nó de substituição.
int remover_no_distribuicao(FILE *file_distribuicao, int pos, char chave[MAXKEY]);

// Função para encontrar o nó máximo em uma subárvore.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Encontra e imprime a distribuição com a chave máxima na subárvore especificada.
void maximo(FILE *file_distribuicao, int pos, char chave[MAXKEY]);

// Função para encontrar o nó mínimo em uma subárvore.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Encontra e imprime a distribuição com a chave mínima na subárvore especificada.
void minimo(FILE *file_distribuicao, int pos, char chave[MAXKEY]);

// Função para imprimir os níveis da árvore de distribuicao com suas respectivas chaves.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: imprime os níveis da árvore na tela ou mensagem de árvore vazia.
void imprimir_niveis(FILE * file_distribuicao);

#endif //DISTRIBUICAO_H
