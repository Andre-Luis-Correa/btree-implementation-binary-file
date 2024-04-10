#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "curso.h"
#include "cabecalho.h"
#include "file.h"

// Função para ler as informações de um curso do usuário e retornar uma struct GRADUACAO
// Pré-condição: Nenhuma
// Pós-condição: Retorna uma struct GRADUACAO com as informações do curso inseridas pelo usuário
GRADUACAO ler_curso(){
    GRADUACAO curso;
    printf("\n--> CADASTRO DE CURSO: \n");
    printf("Insira o codigo do curso: ");
    scanf("%d%*c", &curso.codigo);
    printf("Insira o nome do curso: ");
    scanf("%[^\n]%*c", curso.nome);
    printf("Insira a area do curso: ");
    scanf("%c", &curso.area);

    return curso;
}

// Função para ler um nó em uma determinada posição do arquivo
// Pré-condição: O arquivo deve estar aberto e ser um arquivo de lista, pos deve ser uma posição válida da lista
// Pós-condição: Retorna um ponteiro para o nó lido do arquivo
NO_CURSO * le_no_curso(FILE* file_curso, int pos) {
    NO_CURSO* no_graduacao = (NO_CURSO*)malloc(sizeof(NO_CURSO));
    fseek(file_curso, sizeof(CABECALHO) + pos * sizeof(NO_CURSO), SEEK_SET);
    fread(no_graduacao, sizeof(NO_CURSO), 1, file_curso);
    return no_graduacao;
}

//Escreve um nó em uma determinada posição do arquivo
//Pré-condição: arquivo deve estar aberto e ser um arquivo de lista, pos deve ser uma posição válida do arquivo
//Pós-condição: nó escrito no arquivo
void escreve_no_curso(FILE* file_curso, NO_CURSO * graduacao, int pos) {
    fseek(file_curso, sizeof(CABECALHO) + pos * sizeof(NO_CURSO), SEEK_SET);
    fwrite(graduacao, sizeof(NO_CURSO), 1, file_curso);
}

// Função para buscar um curso no arquivo pelo código
// Pré-condição: O arquivo deve estar aberto, cod é o código a ser buscado, pos é a posição inicial da busca
// Pós-condição: Retorna a posição do curso com o código especificado, -1 se não encontrado
int buscar_curso(FILE * file_curso, int cod, int pos){
    if(pos == -1) return -1; // Caso a raiz seja nula, não ha elementos na arvore
    else{
        NO_CURSO * curso = le_no_curso(file_curso, pos);
        if(curso->curso.codigo > cod) return buscar_curso(file_curso, cod, curso->esq);//todos os codigos menores que a raiz se encontram a esquerda
        else if(curso->curso.codigo < cod) return buscar_curso(file_curso, cod, curso->dir);//todos os codigos maiores que a raiz se encontram a direita
        free(curso);
    }
    return pos;
}

// Função para buscar um nó de curso no arquivo pelo código
// Pré-condição: O arquivo deve estar aberto, cod é o código a ser buscado, pos é a posição inicial da busca
// Pós-condição: Retorna o nó curso com o código especificado, NULL se não encontrado
NO_CURSO * buscar_no_curso(FILE * file_curso, int cod, int pos){
    if(pos == -1) return NULL; // Caso a raiz seja nula, não ha elementos na arvore
    NO_CURSO * curso = le_no_curso(file_curso, pos);
    if(curso->curso.codigo > cod) return buscar_no_curso(file_curso, cod, curso->esq);//todos os codigos menores que a raiz se encontram a esquerda
    else if(curso->curso.codigo < cod) return buscar_no_curso(file_curso, cod, curso->dir);//todos os codigos maiores que a raiz se encontram a direita

    return curso;
}

// Função para buscar um nó de curso no arquivo pelo código
// Pré-condição: O arquivo deve estar aberto, cod é o código a ser buscado, pos é a posição inicial da busca
// Pós-condição: Retorna o nó curso com o código especificado, NULL se não encontrado
NO_CURSO * buscar_info_curso(ARQUIVOS files, int codigo){
    CABECALHO * cab = le_cabecalho(files.file_curso);
    NO_CURSO * no_curso = (NO_CURSO*)malloc(sizeof(NO_CURSO));
    no_curso = buscar_no_curso(files.file_curso, codigo, cab->pos_raiz);
    free(cab);
    return no_curso;
}

// Função para inserir um curso no arquivo
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O curso é inserido no arquivo, e uma mensagem é exibida indicando o resultado da operação

void inserir_curso(FILE* file_curso){
    CABECALHO * cab = le_cabecalho(file_curso);

    NO_CURSO * no_curso = (NO_CURSO*)malloc(sizeof(NO_CURSO));
    no_curso->esq = no_curso->dir = -1;
    no_curso->curso = ler_curso();

    if(buscar_curso(file_curso, no_curso->curso.codigo, cab->pos_raiz) == -1){
        //chama a função recursiva para inserir o curso na árvore
        inserir_curso_rec(file_curso, no_curso, cab->pos_raiz, cab);
        printf("--> Cadastro de curso realizado com sucesso\n");
    }else{
        printf("--> Codigo de curso ja existente\n");
    }

    free(cab);
    free(no_curso);
}

// Função para inserir um curso no arquivo proveniente do arquivo lote txt
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O curso é inserido no arquivo, e uma mensagem é exibida indicando o resultado da operação
void inserir_curso_do_lote(FILE* file_curso, GRADUACAO graduacao){
    CABECALHO * cab = le_cabecalho(file_curso);

    NO_CURSO * no_curso = (NO_CURSO*)malloc(sizeof(NO_CURSO));
    no_curso->esq = no_curso->dir = -1;
    no_curso->curso = graduacao;

    if(buscar_curso(file_curso, no_curso->curso.codigo, cab->pos_raiz) == -1){
        //chama a função recursiva para inserir o curso na árvore
        inserir_curso_rec(file_curso, no_curso, cab->pos_raiz, cab);
        printf("--> Cadastro de curso realizado com sucesso\n");
    }else{
        printf("--> Codigo de curso ja existente\n");
    }

    free(cab);
    free(no_curso);
}

//função recursiva para inserir um curso na árvore
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: O curso é inserido no arquivo, e uma mensagem é exibida indicando o resultado da operação
void inserir_curso_rec(FILE* file_curso, NO_CURSO * no_curso, int pos, CABECALHO * cab){
    if(pos == -1){//pos_raiz == -1 árvore vazia ou a função recebeu uma posição (pos) vazia
        if(is_vazia_arvore(cab)) cab->pos_raiz=0;//cabeca apenas alterada se for a primeira insersão (-1 -> 0)
        escreve_no_curso(file_curso, no_curso, cab->pos_topo);//escreve o novo nó na proxima posicao livre
        cab->pos_topo++;
        escreve_cabecalho(file_curso, cab);
    } else {
        NO_CURSO * prox = le_no_curso(file_curso, pos);
        if(no_curso->curso.codigo < prox->curso.codigo){
            if(prox->esq == -1){
                prox->esq = cab->pos_topo;
                escreve_no_curso(file_curso, prox, pos);
                //chama a função recursiva com pos = -1 para inserir o curso na esquerda
                inserir_curso_rec(file_curso, no_curso, -1, cab);
            } else {
                //chama a função recursiva com pos = prox->esq para inserir o curso na esquerda
                inserir_curso_rec(file_curso, no_curso, prox->esq, cab);
            }
        } else {
            if(no_curso->curso.codigo > prox->curso.codigo){
                if(prox->dir == -1){
                    prox->dir = cab->pos_topo;
                    escreve_no_curso(file_curso, prox, pos);
                    //chama a função recursiva com pos = -1 para inserir o curso na direita
                    inserir_curso_rec(file_curso, no_curso, -1, cab);
                } else {
                    //chama a função recursiva com pos = prox->dir para inserir o curso na direita
                    inserir_curso_rec(file_curso, no_curso, prox->dir, cab);
                }
            }
        }
        free(prox);
    }
}
// Função para imprimir as informações de um curso contidas em um nó
// Pré-condição: O nó deve ser válido
// Pós-condição: As informações do curso no nó são impressas na tela
void imprimir_info_curso(NO_CURSO * no_graduacao) {
    printf("| %03d    ", no_graduacao->curso.codigo);
    printf("%-50s", no_graduacao->curso.nome);
   // printf("esq: %d   dir: %d  ", no_graduacao->esq, no_graduacao->dir);
    printf("%c  |\n", no_graduacao->curso.area);
}

// Função para imprimir os cursos em ordem no arquivo
// Pré-condição: O arquivo deve estar aberto e conter cursos
// Pós-condição: Os cursos são impressos em ordem na tela

void imprimir_in_order_curso(FILE* file_curso, int pos_atual){
    if (pos_atual != -1) {
        NO_CURSO * no_atual = le_no_curso(file_curso, pos_atual);

        // Recursivamente imprime a subárvore esquerda
        imprimir_in_order_curso(file_curso, no_atual->esq);

        imprimir_info_curso(no_atual);

        // Recursivamente imprime a subárvore direita
        imprimir_in_order_curso(file_curso, no_atual->dir);
    }
}

// Função para imprimir todos os cursos em ordem no arquivo
// Pré-condição: O arquivo deve estar aberto
// Pós-condição: Os cursos são impressos em ordem na tela
void imprimir_lista_cursos(FILE* file_curso) {
    CABECALHO *cab = le_cabecalho(file_curso);

    if(is_vazia_arvore(cab)) printf("--> Nao ha cursos cadastrados\n");
    else{
        printf(" ----------------------- Lista de Cursos ---------------------\n");
        printf("| COD.   NOME                                            AREA |\n");
        imprimir_in_order_curso(file_curso, cab->pos_raiz);
        printf(" -------------------------------------------------------------\n");
    }

    free(cab);
}
