#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "distribuicao.h"
#include "cabecalho.h"
#include "file.h"
#include "curso.h"
#include "disciplina.h"
#include "professor.h"

// Função para ler os dados de uma distribuição do usuário.
// Pré-condição: Nenhuma.
// Pós-condição: Retorna uma distribuição lida do usuário.
DISTRIBUICAO ler_distribuicao (){
    DISTRIBUICAO distribuicao;

    printf ("Insira o codigo da disciplina: ");
    scanf ("%d%*c", &distribuicao.cod_disciplina);
    printf ("Insira o ano letivo: ");
    scanf ("%[^\n]%*c", distribuicao.ano_letivo);
    printf ("Insira o codigo do professor: ");
    scanf ("%d", &distribuicao.cod_professor);

    return distribuicao;
}

// Função para ler os NO de uma distribuição do usuário.
// Pré-condição: Pos precisa ser uma posição valida no arquivo.
// Pós-condição: retorna um nó distribuição
NO_DISTRIBUICAO * le_no_distribuicao (FILE * file_distribuicao, int pos){
    NO_DISTRIBUICAO * no_distribuicao = (NO_DISTRIBUICAO*)malloc(sizeof (NO_DISTRIBUICAO));
    fseek (file_distribuicao, sizeof (CABECALHO) + pos * sizeof (NO_DISTRIBUICAO), SEEK_SET);
    fread (no_distribuicao, sizeof (NO_DISTRIBUICAO), 1, file_distribuicao);
    return no_distribuicao;
}

// Função para escrever um nó no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Escreve o nó no arquivo de distribuições na posição especificada.
void escreve_no_distribuicao (FILE * file_distribuicao, NO_DISTRIBUICAO * no_distribuicao, int pos){
    fseek (file_distribuicao, sizeof (CABECALHO) + pos * sizeof (NO_DISTRIBUICAO), SEEK_SET);
    fwrite (no_distribuicao, sizeof (NO_DISTRIBUICAO), 1, file_distribuicao);
}

// Função para buscar uma distribuição no arquivo com base na chave.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Retorna a posição no arquivo onde a distribuição com a chave foi encontrada.
int buscar_distribuicao(FILE * file_distribuicao, char chave[MAXKEY], int pos){
    //faz a busca no metodo árvore binaria de busca
    if(pos == -1) return -1;
    else{
        NO_DISTRIBUICAO * no_distribuicao = le_no_distribuicao(file_distribuicao, pos);

        if(strcmp(chave, no_distribuicao->distribuicao.cod_distribuicao) < 0) return buscar_distribuicao(file_distribuicao, chave, no_distribuicao->esq); //todos os codigos menores que a raiz se encontram a esquerda
        else if(strcmp(chave, no_distribuicao->distribuicao.cod_distribuicao) > 0) return buscar_distribuicao(file_distribuicao, chave, no_distribuicao->dir); //todos os codigos maiores que a raiz se encontram a direita

        free(no_distribuicao);
    }
    return pos;
}

// Função para formatar o código da distribuição.
// Pré-condição: Nenhuma.
// Pós-condição: O parâmetro 'codigo' é preenchido com o código formatado.
void formatar_codigo(int codigo_disciplina, char ano_letivo[5], char codigo[MAXKEY]) {
    // Copiar os primeiros 4 caracteres do ano letivo para o código
    strncpy(codigo, ano_letivo, 4);

    // Copiar os dois dígitos do código da disciplina no final do ano letivo
    snprintf(codigo + 4, 4, "%02d", codigo_disciplina);

    // Garantir que a string seja terminada corretamente
    codigo[MAXKEY - 1] = '\0';
}

// Função para inserir uma distribuição.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere uma nova distribuição no arquivo.
void inserir_distribuicao(FILE* file_distribuicao){
    CABECALHO * cab = le_cabecalho(file_distribuicao);

    NO_DISTRIBUICAO * no_distribuicao = (NO_DISTRIBUICAO*)malloc(sizeof(NO_DISTRIBUICAO));

    no_distribuicao->esq = no_distribuicao->dir = -1; // É um novo nó, logo os filhos da esquerda e direita apontam para NULL (-1)

    no_distribuicao->distribuicao = ler_distribuicao();

    formatar_codigo(no_distribuicao->distribuicao.cod_disciplina, no_distribuicao->distribuicao.ano_letivo, no_distribuicao->distribuicao.cod_distribuicao);

    if(buscar_distribuicao(file_distribuicao, no_distribuicao->distribuicao.cod_distribuicao, cab->pos_raiz) == -1){
        inserir_distribuicao_file(file_distribuicao, no_distribuicao);
        printf("--> Cadastro de distribuicao realizado com sucesso\n");
    }else{
        printf("--> Ja existe cadastro existente com o codigo de disciplina e ano letivo informado\n");
    }

    free(cab);
    free(no_distribuicao);
}

// Função para inserir uma distribuição proveniente do arquivo lote txt no arquivo binário.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere uma nova distribuição no arquivo.
void inserir_distribuicao_do_lote(FILE* file_distribuicao, DISTRIBUICAO distribuicao){
    CABECALHO * cab = le_cabecalho(file_distribuicao);

    NO_DISTRIBUICAO * no_distribuicao = (NO_DISTRIBUICAO*)malloc(sizeof(NO_DISTRIBUICAO));

    no_distribuicao->esq = no_distribuicao->dir = -1; // É um novo nó, logo os filhos da esquerda e direita apontam para NULL (-1)

    no_distribuicao->distribuicao = distribuicao;

    formatar_codigo(no_distribuicao->distribuicao.cod_disciplina, no_distribuicao->distribuicao.ano_letivo, no_distribuicao->distribuicao.cod_distribuicao);

    if(buscar_distribuicao(file_distribuicao, no_distribuicao->distribuicao.cod_distribuicao, cab->pos_raiz) == -1){
        inserir_distribuicao_file(file_distribuicao, no_distribuicao);
        printf("--> Cadastro de distribuicao realizado com sucesso\n");
    }else{
        printf("--> Ja existe cadastro existente com o codigo de disciplina e ano letivo informado\n");
    }

    free(cab);
    free(no_distribuicao);
}

// Função para inserir uma distribuição no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo de distribuições.
void inserir_distribuicao_file(FILE* file_distribuicao, NO_DISTRIBUICAO * no_distribuicao){
    CABECALHO * cab = le_cabecalho(file_distribuicao);

    // Se a árvore não possui nós livres
    if(cab->pos_livre == -1) inserir_sem_nos_livres(file_distribuicao, no_distribuicao, cab->pos_raiz);
    // Se a árvore possui nós livres
    else inserir_com_nos_livres(file_distribuicao, no_distribuicao, cab->pos_raiz);

    free(cab);
}

// Função para inserir um nó sem considerar nós livres.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo sem considerar nós livres.
void inserir_sem_nos_livres(FILE* file_distribuicao, NO_DISTRIBUICAO * no_distribuicao, int pos){
    CABECALHO * cab = le_cabecalho(file_distribuicao);

    if(pos == -1){//pos_raiz == -1 árvore vazia ou a função recebeu uma posição (pos) vazia
        if(is_vazia_arvore(cab)) cab->pos_raiz=0;//cabeca apenas alterada se for a primeira insersão (-1 -> 0)
        escreve_no_distribuicao(file_distribuicao, no_distribuicao, cab->pos_topo);//escreve o novo nó na proxima posicao livre
        cab->pos_topo++;
        escreve_cabecalho(file_distribuicao, cab);
    }
    else{
        NO_DISTRIBUICAO * prox_no = le_no_distribuicao(file_distribuicao, pos);

        //if (strcmp(no_distribuicao->distribuicao.cod_distribuicao, prox_no->distribuicao.cod_distribuicao)) == 0 return;
        if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, prox_no->distribuicao.cod_distribuicao) < 0){
            if(prox_no->esq == -1){
            //se o filho a esquerda é vazio, é nele que será feita a insersão
            //logo, é necesario alterar a posicao esquerda como sendo a posicao que o ramo esquerdo será inserido
                prox_no->esq = cab->pos_topo;
                escreve_no_distribuicao(file_distribuicao, prox_no, pos);
                inserir_sem_nos_livres(file_distribuicao, no_distribuicao, -1);//como a posicao esquerda foi alterada, manda-se -1
            } else inserir_sem_nos_livres(file_distribuicao, no_distribuicao, prox_no->esq);//envia a proxima posicao para ser testada
        }
        else {
            if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, prox_no->distribuicao.cod_distribuicao) > 0){
                if(prox_no->dir == -1){
                //se o filho a direita é vazio, é nele que será feita a insersão
                //logo, é necesario alterar a posicao direita como sendo a posicao que o ramo direito será inserido
                    prox_no->dir = cab->pos_topo;
                    escreve_no_distribuicao(file_distribuicao, prox_no, pos);
                    inserir_sem_nos_livres(file_distribuicao, no_distribuicao, -1);//como a posicao direita foi alterada, manda-se -1
                }else inserir_sem_nos_livres(file_distribuicao, no_distribuicao, prox_no->dir);//envia a proxima posicao para ser testada
            }
        }
        free(prox_no);
    }
    free(cab);
}

// Função para inserir um nó considerando nós livres.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Insere um novo nó no arquivo considerando nós livres.
void inserir_com_nos_livres(FILE* file_distribuicao, NO_DISTRIBUICAO * no_distribuicao, int pos){
    CABECALHO * cab = le_cabecalho(file_distribuicao);

    if(pos == -1){//se arvore vazia (pos_raiz == -1) ou posicao vazia (no_distribuicao->(esq || dir) == -1)
        NO_DISTRIBUICAO * no_livre = le_no_distribuicao(file_distribuicao, cab->pos_livre);//primeiro guarda a antiga posicao livre
        escreve_no_distribuicao(file_distribuicao, no_distribuicao, cab->pos_livre);//escreve o novo nó na posicao livre
        if(is_vazia_arvore(cab)) cab->pos_raiz = cab->pos_livre; //ultima posicao removida é sempre a raiz (0), entao pos_raiz=0
        cab->pos_livre = no_livre->esq;//nova cabeça da lista de nós livres é a próxima posicao do no livre reencadeado na árvore
        escreve_cabecalho(file_distribuicao, cab);
        free(no_livre);
    } else {
        NO_DISTRIBUICAO * prox_no = le_no_distribuicao(file_distribuicao, pos);

        if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, prox_no->distribuicao.cod_distribuicao) < 0){
            if(prox_no->esq == -1){
                //se o filho a esquerda é vazio, é nele que será feito a insersão
                //logo, é necessário setar a posicão esquerda como a próxima posicao livre (posLivre) em que ele será inserido
                prox_no->esq = cab->pos_livre;
                escreve_no_distribuicao(file_distribuicao, prox_no, pos);
                inserir_com_nos_livres(file_distribuicao, no_distribuicao, -1);
            }
            inserir_com_nos_livres(file_distribuicao, no_distribuicao, prox_no->esq);
        } else{
            if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, prox_no->distribuicao.cod_distribuicao) > 0){
                if(prox_no->dir == -1){
                    //se o filho a direita é vazio, é nele que será feito a insersão
                    //logo, é necessário setar a posicão direita como a próxima posicao livre (posLivre) em que ele será inserido
                    prox_no->dir = cab->pos_livre;
                    escreve_no_distribuicao(file_distribuicao, prox_no, pos);
                    inserir_com_nos_livres(file_distribuicao, no_distribuicao, -1);
                }
                inserir_com_nos_livres(file_distribuicao, no_distribuicao, prox_no->dir);
            }
        }
        free(prox_no);
    }
    free(cab);
}

// Função para imprimir as informações de uma distribuição.
// Pré-condição: Nenhuma.
// Pós-condição: Imprime as informações do nó de distribuição.
void imprimir_info_distribuicao(ARQUIVOS files, NO_DISTRIBUICAO * no_distribuicao){
    NO_DISCIPLINA * no_disciplina;
    NO_PROFESSOR * no_professor;
    NO_CURSO * graduacao;

    int pos_disciplina = buscar_disciplina(files.file_disciplina, no_distribuicao->distribuicao.cod_disciplina, 0);
    no_disciplina = le_no_disciplina(files.file_disciplina, pos_disciplina);

    int pos_professor = buscar_professor(files.file_professor, no_distribuicao->distribuicao.cod_professor, 0);
    no_professor = le_no_professor(files.file_professor, pos_professor);

    int pos_curso = buscar_curso(files.file_curso, no_disciplina->disciplina.cod_curso, 0);
    graduacao = le_no_curso(files.file_curso, pos_curso);

    printf("|%7s        %-7d    %-40s      %-12s     %-8d     %-50s   %-12d     %-40s|\n",
        no_distribuicao->distribuicao.cod_distribuicao, no_distribuicao->distribuicao.cod_disciplina, no_disciplina->disciplina.nome,
        no_distribuicao->distribuicao.ano_letivo, no_distribuicao->distribuicao.cod_professor, no_professor->professor.nome, no_disciplina->disciplina.cod_curso, graduacao->curso.nome);

    free(no_disciplina);
    free(no_professor);
    free(graduacao);
}

// Função para imprimir as distribuições em ordem no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime as distribuições do arquivo em ordem a partir da posição especificada.
void imprimir_in_order_distribuicao(ARQUIVOS files, FILE* file_distribuicao, int pos_atual) {
    if (pos_atual != -1) {
        NO_DISTRIBUICAO * no_atual = le_no_distribuicao(file_distribuicao, pos_atual);

        // Recursivamente imprime a subárvore esquerda
        imprimir_in_order_distribuicao(files, file_distribuicao, no_atual->esq);

        imprimir_info_distribuicao(files, no_atual);

        // Recursivamente imprime a subárvore direita
        imprimir_in_order_distribuicao(files, file_distribuicao, no_atual->dir);
    }
}

// Função para imprimir a lista de distribuições no arquivo.
// Pré-condição: Os arquivos no struct ARQUIVOS devem estar abertos.
// Pós-condição: Imprime a lista de distribuições do arquivo.
void imprimir_lista_distribuicao(ARQUIVOS files) {
    CABECALHO* cab = le_cabecalho(files.file_distribuicao);

    if(is_vazia_arvore(cab)) printf("--> Nao ha distribuicoes cadastradas\n");
    else{
        printf(" -------------------------------------------------------------------------------------------Distribuicao de Disciplina ----------------------------------------------------------------------------------------------\n");
        printf("| COD.      COD. DISC.     DISCIPLINA                                 ANO LETIVO       COD. PROF.      PROFESSOR                                       COD. CURSO            NOME DO CURSO                           |\n");
        imprimir_in_order_distribuicao(files, files.file_distribuicao, cab->pos_raiz);
        printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
    }

    free(cab);
}

// Função para remover uma distribuição.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Remove uma distribuição do arquivo.

void retira_distribuicao(FILE* file_distribuicao){
    CABECALHO* cab = le_cabecalho(file_distribuicao);

    int cod;
    char ano_letivo[5];
    char chave[MAXKEY];

    printf ("Insira o codigo da disciplina: ");
    scanf ("%d%*c", &cod);
    printf ("Insira o ano letivo: ");
    scanf ("%[^\n]%*c", ano_letivo);

    formatar_codigo(cod, ano_letivo, chave);

    remover_no_distribuicao(file_distribuicao, cab->pos_raiz, chave);

    free(cab);
}

// Função para remover um nó de distribuição.
// Pré-condição: O arquivo file_distribuicao deve estar aberto, pos deve ser uma chave valida
// Pós-condição: Remove uma distribuição do arquivo.
int remover_no_distribuicao(FILE* file_distribuicao, int pos, char chave[MAXKEY]){
        CABECALHO* cab = le_cabecalho(file_distribuicao);

        if(pos == -1){
            if(is_vazia_arvore(cab)) printf("\nNao ha distribuicoes cadastradas");
            else printf("\nCodigo nao existe ");
            printf("Nao foi possivel realizar a remocao\n");
            return -1;
        }//se posCabeca for -1 (arvore vazia) ou se no_distribuicao->(esq || drt) for -1 (filhos vazios)
        else{
            NO_DISTRIBUICAO * no_distribuicao = le_no_distribuicao(file_distribuicao, pos);

            if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, chave) > 0){//todos os codigos menores que a raiz se encontram a esquerda
                no_distribuicao->esq = remover_no_distribuicao(file_distribuicao, no_distribuicao->esq, chave);//pode receber novamente sua propria posicao esquerda ou -1 (ramo-folha removido)
                escreve_no_distribuicao(file_distribuicao, no_distribuicao, pos);
            }
            else{
                if(strcmp(no_distribuicao->distribuicao.cod_distribuicao, chave) < 0){//todos os codigos maiores que a raiz se encontram a direita
                    no_distribuicao->dir = remover_no_distribuicao(file_distribuicao, no_distribuicao->dir, chave);//pode receber novamente sua propria posicao direito ou -1 (ramo-folha removido)
                    escreve_no_distribuicao(file_distribuicao, no_distribuicao, pos);
                }
                else{//nó encontrado
                    if(no_distribuicao->esq == -1 && no_distribuicao->dir == -1){
                    //nó folha. esse é o nó que será removido
                    //encadeia-se a lista de nós livres
                        if(pos == cab->pos_raiz) cab->pos_raiz = -1;//árvore fica vazia
                        no_distribuicao->esq = no_distribuicao->dir = cab->pos_livre;
                        cab->pos_livre = pos;
                        escreve_cabecalho(file_distribuicao, cab);//escreve o cabecalho atualizado
                        escreve_no_distribuicao(file_distribuicao, no_distribuicao, pos);
                        pos = -1;//sinaliza que essa folha foi removida e -1 (null) retorna para sua raiz imediata
                        printf("\nDistribuicao removida com sucesso\n");
                    }
                    else{
                        if(no_distribuicao->esq==-1){//possui apenas ramo direito
                            char chave_min[MAXKEY];
                            minimo(file_distribuicao, no_distribuicao->dir, chave_min);//recebe o menor codigo do ramo direito

                            trocar_info(file_distribuicao, pos, buscar_distribuicao(file_distribuicao, chave_min, cab->pos_raiz));

                            no_distribuicao = le_no_distribuicao(file_distribuicao, pos);//lê a nova arvore que teve suas informacoes trocacadas
                            no_distribuicao->dir = remover_no_distribuicao(file_distribuicao, no_distribuicao->dir, chave_min);//remove o no minimo cujo as informacoes foram copiadas
                            escreve_no_distribuicao(file_distribuicao, no_distribuicao, pos);//escreve novamente a arvore atualizada
                        }
                        else{//possui apenas ramo esquerdo ou dois ramos
                            char chave_max[MAXKEY];
                            maximo(file_distribuicao, no_distribuicao->esq, chave_max);

                            trocar_info(file_distribuicao, pos, buscar_distribuicao(file_distribuicao, chave_max, cab->pos_raiz));

                            no_distribuicao = le_no_distribuicao(file_distribuicao, pos);//lê a nova arvore que teve suas informacoes copiadas do no maximo

                            no_distribuicao->esq = remover_no_distribuicao(file_distribuicao, no_distribuicao->esq, chave_max);//remove o no minimo cujo as informacoes foram copiadas
                            escreve_no_distribuicao(file_distribuicao, no_distribuicao, pos);//escreve novamente a arvore atualizada
                        }
                    }
                }
            }
            free(no_distribuicao);
        }
        free(cab);

    return pos;
}

// Função para troca de distribuições
// Pré-condição: O arquivo file_distribuicao deve estar aberto, pos_destino e pos_origem devem ser posiçes validas no arquivo
// Pós-condição: Troca as informações entre dois nós no arquivo.
void trocar_info(FILE* file_distribuicao, int pos_destino, int pos_origem){
        NO_DISTRIBUICAO * destino = le_no_distribuicao(file_distribuicao, pos_destino);
        NO_DISTRIBUICAO * origem = le_no_distribuicao(file_distribuicao, pos_origem);

        NO_DISTRIBUICAO * aux=(NO_DISTRIBUICAO*)malloc(sizeof(NO_DISTRIBUICAO));

        aux->distribuicao.cod_disciplina = destino->distribuicao.cod_disciplina;
        strcpy(aux->distribuicao.ano_letivo, destino->distribuicao.ano_letivo);
        aux->distribuicao.cod_professor = destino->distribuicao.cod_professor;

        strcpy(destino->distribuicao.cod_distribuicao, origem->distribuicao.cod_distribuicao);
        destino->distribuicao.cod_disciplina = origem->distribuicao.cod_disciplina;
        strcpy(destino->distribuicao.ano_letivo, origem->distribuicao.ano_letivo);
        destino->distribuicao.cod_professor = origem->distribuicao.cod_professor;

        origem->distribuicao.cod_disciplina = aux->distribuicao.cod_disciplina;
        strcpy(origem->distribuicao.ano_letivo, aux->distribuicao.ano_letivo);
        origem->distribuicao.cod_professor = aux->distribuicao.cod_professor;

        escreve_no_distribuicao(file_distribuicao, destino, pos_destino);
        escreve_no_distribuicao(file_distribuicao, origem, pos_origem);

        free(destino);
        free(origem);
        free(aux);
    }

// Função para encontrar o nó máximo em uma subárvore.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Encontra e imprime a distribuição com a chave máxima na subárvore especificada.
void maximo(FILE* file_distribuicao, int pos, char chave[MAXKEY]){
    NO_DISTRIBUICAO * no_distribuicao = le_no_distribuicao(file_distribuicao, pos);
    strcpy(chave, no_distribuicao->distribuicao.cod_distribuicao);
    pos=no_distribuicao->dir;//faz a busca do ultimo nó, passando apenas pelos ramos da direito das sub-arvores
    free(no_distribuicao);
    if(pos!=-1) maximo(file_distribuicao, pos, chave);
}


// Função para encontrar o nó mínimo em uma subárvore.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Encontra e imprime a distribuição com a chave mínima na subárvore especificada.
void minimo(FILE* file_distribuicao, int pos, char chave[MAXKEY]){
    NO_DISTRIBUICAO * no_distribuicao = le_no_distribuicao(file_distribuicao, pos);
    strcpy(chave, no_distribuicao->distribuicao.cod_distribuicao);
    pos=no_distribuicao->esq;//faz a busca do ultimo nó, passando apenas pelos ramos da esqueda das sub-arvores
    free(no_distribuicao);
    if(pos!=-1) minimo(file_distribuicao, pos, chave);;
}


// Função para imprimir a lista de posições livres no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime a lista de posições livres no arquivo a partir da posição especificada.
void imprimir_posicoes_livres(FILE* file_distribuicao, int pos) {
    NO_DISTRIBUICAO * no_atual = le_no_distribuicao(file_distribuicao, pos);

    if(pos != -1){
        printf("|%4d                              %-8s|\n", pos, no_atual->distribuicao.cod_distribuicao);
        imprimir_posicoes_livres(file_distribuicao, no_atual->esq);
        free(no_atual);
    }

}

// Função para imprimir a lista de posições livres no arquivo.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: Imprime a lista de posições livres no arquivo.
void imprimir_posicoes_livres_wrapper(FILE* file_distribuicao) {
    CABECALHO* cab = le_cabecalho(file_distribuicao);

    if (cab->pos_livre != -1) {
        printf("-------Lista de Posicoes Livres------------\n");
        printf("|POSICAO                           CHAVE   |\n");
        imprimir_posicoes_livres(file_distribuicao, cab->pos_livre);
        printf("-------------------------------------------");
    }else{
        printf("--> Nao ha posicoes livres\n");
    }
}

// Função para imprimir os níveis da árvore de distribuicao com suas respectivas chaves.
// Pré-condição: O arquivo file_distribuicao deve estar aberto.
// Pós-condição: imprime os níveis da árvore na tela ou mensagem de árvore vazia.
void imprimir_niveis(FILE * file_distribuicao) {
    // Verifica se a árvore está vazia
    CABECALHO* cab = le_cabecalho(file_distribuicao);

    if (cab->pos_raiz == -1) {
        printf("Árvore vazia\n");
        return;
    }

    // Fila para armazenar os nós a serem processados
    int * fila = (int *)malloc(cab->pos_topo * sizeof(int));
    int frente = 0;
    int fim = 0;
    // Adiciona a raiz à fila
    fila[fim++] = cab->pos_raiz;
    printf("-->   Impressao de Arvore por niveis\n");

    while (frente < fim) {
        // Número de nós no nível atual
        int elementos_nivel = fim - frente;

        // Imprime as chaves dos nós no nível atual
        for (int i = 0; i < elementos_nivel; i++) {
            // Lê o nó atual
            NO_DISTRIBUICAO * no_atual = le_no_distribuicao(file_distribuicao, fila[frente + i]);

            printf("%s ", no_atual->distribuicao.cod_distribuicao);


            // Adiciona os filhos não nulos à fila
            if (no_atual->esq != -1) {
                fila[fim++] = no_atual->esq;
            }
            if (no_atual->dir != -1) {
                fila[fim++] = no_atual->dir;
            }
        }

        printf("\n");

        // Atualiza a frente para o próximo nível
        frente += elementos_nivel;
    }

    free(fila);
    free(cab);
}
