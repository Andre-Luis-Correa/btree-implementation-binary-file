//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto_insercao.h"
#include "../utils/arvore_utils.h"
#include "../impressao/produto_impressao.h"

// Função para ler os dados de um produto
// Pré-condição: nenhuma
// Pós-condição: retorna um ponteiro para a estrutura PRODUTO_DATA preenchida com os dados inseridos pelo usuário
PRODUTO_DATA * ler_produto() {
    PRODUTO_DATA * produto = (PRODUTO_DATA*) malloc(sizeof (PRODUTO_DATA));

    printf("\n--> CADASTRO DE PRODUTO: \n");
    printf("Insira o codigo do produto: ");
    scanf("%d", &produto->codigo);
    printf("Insira o nome do produto: ");
    scanf(" %[^\n]", produto->nome);
    printf("Insira a marca do produto: ");
    scanf(" %[^\n]", produto->marca);
    printf("Insira a categoria do produto: ");
    scanf(" %[^\n]", produto->categoria);
    printf("Insira a quantidade em estoque do produto: ");
    scanf("%d", &produto->estoque);
    printf("Insira o preco do produto: ");
    scanf("%f", &produto->preco);

    return produto;
}

// Verifica se um nó da árvore B está em overflow
// Pré-condição: o nó deve existir
// Pós-condição: retorna 1 se o número de chaves for igual à ordem da árvore, 0 caso contrário
int overflow (ARVOREB * r){
    return r->num_chaves == ORDEM;
}

// Função para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices deve existir e estar aberto para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
void cadastrar_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    PRODUTO_DATA * produto = ler_produto();

    if(buscar_no(files.file_indices, produto->codigo) == -1){
        // Realizar a inserção do nó, pois ainda não existe esse código na árvore
        printf("\n---> Nova insercao!\n");
        cadastrar_produto_file(files, produto);
    }else{
        printf("\nATENCAO: Codigo de produto ja existente!\n");
    }

    free(cab_indices);
    free(produto);
}

// Cria um novo nó na árvore B
// Pré-condição: nenhuma
// Pós-condição: o nó é criado com as informações passadas por parâmetro
void cria_no(ARVOREB * r, int codigo, int pos_dados) {
    r->chave[0] = codigo;
    r->num_chaves = 1;
    r->prox_livre = -1;
    r->pt_dados[0] = pos_dados;
    for(int i = 0; i < ORDEM+1; i++)
        r->filho[i] = -1;
}

// Cria um novo registro com os dados de um produto
// Pré-condição: nenhuma
// Pós-condição: o registro é criado com os dados do produto
void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto){
    dados->produto = *produto;
    dados->prox_livre = -1;
}

// Função para dividir um nó da árvore B em dois
// Pré-condição: o nó x deve existir e não estar vazio
// Pós-condição: divide o nó x em dois nós, retornando a posição do novo nó criado
int split (ARQUIVOS files, ARVOREB * x, int pos, int * meio, int * pos_meio, CABECALHO_INDICES * cab_indices){
    ARVOREB * y = (ARVOREB*) malloc (sizeof(ARVOREB));

    // O "q" representa o a metade do nó
    int q = x->num_chaves/2;
    y->num_chaves = x->num_chaves - q - 1;
    x->num_chaves = q;

    escreve_no(files.file_indices, x, pos);

    *meio = x->chave[q];
    *pos_meio = x->pt_dados[q];

    int i;
    y->filho[0] = x->filho[q+1];
    for (i = 0 ; i < y->num_chaves ; i++){
        y->chave[i] = x->chave[q+i+1];
        y->pt_dados[i] = x->pt_dados[q+i+1];
        y->filho[i+1] = x->filho[q+i+2];
    }

    int pos_y = get_pos_livre_indices(files.file_indices, cab_indices);
    escreve_no(files.file_indices, y, pos_y);
    free(y);
    escreve_cabecalho_indices(files.file_indices, cab_indices);
    return pos_y;
}

// Obtém a próxima posição livre no arquivo de dados
// Pré-condição: o arquivo de dados deve estar aberto para leitura e escrita
// Pós-condição: retorna a próxima posição livre no arquivo de dados
int get_pos_livre_dados(FILE * file, CABECALHO_DADOS * cab){
    if(cab->pos_livre == -1){
        int nova_pos = cab->pos_topo;
        cab->pos_topo++;
        return nova_pos;
    }

    int pos_livre = cab->pos_livre;
    DADOS_REGISTRO * registro = ler_registro(file, cab->pos_livre);

    cab->pos_livre = registro->prox_livre;
    escreve_cabecalho_dados(file, cab);
    free(registro);

    return pos_livre;
}

// Obtém a próxima posição livre no arquivo de índices
// Pré-condição: o arquivo de índices deve estar aberto para leitura e escrita
// Pós-condição: retorna a próxima posição livre no arquivo de índices
int get_pos_livre_indices(FILE * file, CABECALHO_INDICES * cab){
    if(cab->pos_livre == -1){
        int nova_pos = cab->pos_topo;
        cab->pos_topo++;
        return nova_pos;
    }

    int pos_livre = cab->pos_livre;
    ARVOREB * no = ler_no(file, cab->pos_livre);

    cab->pos_livre = no->prox_livre;
    escreve_cabecalho_indices(file, cab);
    free(no);

    return pos_livre;
}

// Função principal para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices e o arquivo de dados devem existir e estar abertos para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
void cadastrar_produto_file(ARQUIVOS files, PRODUTO_DATA * produto){

    // Faz a leitura dos cabeçalhos
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    ARVOREB * r = (ARVOREB*) malloc(sizeof (ARVOREB));
    DADOS_REGISTRO * dados = (DADOS_REGISTRO *) malloc(sizeof (DADOS_REGISTRO));
    int pos_raiz = cab_indices->pos_raiz;
    int pos_registro;

    if (pos_raiz == -1) { // pos -> pos_raiz == -1 árvore vazia ou a função recebeu uma posição (pos) vazia
        // Atualiza a posição da raiz para o topo do arquivo
        cab_indices->pos_raiz = cab_indices->pos_topo;

        // Escreve no arquivo de dados as informações do produto a ser inserido
        cria_registro(dados, produto);
        pos_registro = get_pos_livre_dados(files.file_dados, cab_dados);
        escreve_registro(files.file_dados, dados, pos_registro);

        // Cria a raiz com as informações: código do produto e o ponteiro de dados do arquivo de dados
        cria_no(r, produto->codigo, pos_registro);
        escreve_no(files.file_indices, r, get_pos_livre_indices(files.file_indices, cab_indices));

        escreve_cabecalho_indices(files.file_indices, cab_indices);
        escreve_cabecalho_dados(files.file_dados, cab_dados);
    } else { // árvore não vazia

        ARVOREB * raiz = ler_no(files.file_indices, pos_raiz); // Lê a raiz da árvore

        DADOS_REGISTRO * dados_novos = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO)); // Cria um registro e escreve no arquivo de dados
        cria_registro(dados_novos, produto);

        // Guarda a informação de onde o novo registro foi inserido no arquivo de dados
        int pt_dados_atual = get_pos_livre_dados(files.file_dados, cab_dados);

        // ATENÇÃO: reaproveitamento de posições
        escreve_registro(files.file_dados, dados_novos, pt_dados_atual);
        free(dados_novos);

        // Atualiza o cabecalho do ARQUIVO de DADOS
        escreve_cabecalho_dados(files.file_dados, cab_dados);

        // Chama a função auxiliar de inserção
        // Os parâmetros são: Os arquivos (AMBOS), código do produto, ponteiro de dado do produto, posição da raiz
        cadastrar_aux (files, raiz, produto->codigo, pt_dados_atual, cab_indices->pos_raiz, cab_indices);

        // Lê o cabeçalho atual do arquivo de índices
        CABECALHO_INDICES * cab_indices_atual = le_cabecalho_indices(files.file_indices);

        if(overflow(raiz)){
            int meio, pos_meio, arvore_x;

            arvore_x = split(files, raiz, cab_indices_atual->pos_raiz, &meio, &pos_meio, cab_indices_atual);

            ARVOREB * nova_raiz = (ARVOREB*) malloc(sizeof (ARVOREB));
            nova_raiz->chave[0] = meio;
            nova_raiz->pt_dados[0] = pos_meio;
            nova_raiz->filho[0] = cab_indices_atual->pos_raiz;
            nova_raiz->filho[1] = arvore_x;
            for (int i = (((int) ORDEM/2) +1) ; i < ORDEM ; i++){
                raiz->filho[i] = -1;
            }
            nova_raiz->num_chaves = 1;

            int pos_nova_raiz = get_pos_livre_indices(files.file_indices, cab_indices_atual);
            escreve_no(files.file_indices, nova_raiz, pos_nova_raiz);
            cab_indices_atual->pos_raiz = pos_nova_raiz;

            escreve_cabecalho_indices(files.file_indices, cab_indices_atual);
            free(nova_raiz);
        }
        free(raiz);
        free(cab_indices_atual);
    }

    free(r);
    free(dados);
    free(cab_indices);
    free(cab_dados);
    printf("\n---> Insercao realizada com sucesso!\n");
}

// Função para encontrar a posição onde uma chave deve ser inserida em um nó da árvore B
// Pré-condição: o nó r deve existir e não estar vazio
// Pós-condição: retorna 1 se a chave já existe no nó, caso contrário retorna 0 e atualiza a posição onde a chave deve ser inserida
int busca_pos (ARVOREB * r, int codigo, int * pos){
    // O loop busca pela posição onde a nova chave (codigo) deveria entrar
    for ((*pos) = 0 ; (*pos) < r->num_chaves ; (*pos)++){
        if (codigo == r->chave[(*pos)]){
            return 1;
        }
        else if (codigo < r->chave[(*pos)]){
            break;
        }
    }

    return 0;
}

// Função para adicionar uma chave e seu ponteiro de dados à direita de uma posição específica em um nó da árvore B
// Pré-condição: o nó r deve existir e não estar cheio
// Pós-condição: a chave e seu ponteiro de dados são inseridos na posição especificada
void adiciona_direita (ARVOREB * r, int pos, int codigo, int pt_dados, int p){
    int i;

    // Desloca todas as chaves e pt_dados e filhos para frente da pos encontrada, deixondo-a livre
    for (i = r->num_chaves ; i > pos ; i--){
        r->chave [i] = r->chave[i-1];
        r->pt_dados[i] = r->pt_dados[i-1];
        r->filho[i+1] = r->filho[i];
    }

    // A nova chave (codigo) é inserida na posição livre
    r->chave[pos] = codigo;

    // O ponteiro de dados da nova chave tambpem é inserido na posição livre, após deslocamento
    r->pt_dados[pos] = pt_dados;

    // O filho à direita da chave na posição os recebe a pos "p"
    r->filho[pos+1] = p;

    // Incrementa o número de chaves, devido a inserção do novo código
    r->num_chaves++;
}

// Função auxiliar para cadastrar um produto na árvore B
// Pré-condição: o arquivo de índices deve existir e estar aberto para escrita
// Pós-condição: o produto é cadastrado na árvore B e nos dados, se o código do produto ainda não existir na árvore
// Os parâmetros são: Os arquivos (AMBOS), código do produto, ponteiro de dado do produto, posição da raiz (Na 1° chamada)
void cadastrar_aux(ARQUIVOS files, ARVOREB * r, int codigo, int pt_dados, int pos_atual, CABECALHO_INDICES * cab_indices){
    // Variável para armazenar a posiçao na qual uma determinada chave deveria entrar
    int pos;

    if(!busca_pos(r, codigo, &pos)){

        // A função eh-folha verifica se o nó r é folha
        if (eh_folha(r)){
            // Caso o nó seja uma folha a inserção é feita nele mesmo: EM UMA ÁRVORE B A INSERÇÃO É SEMPRE NA FOLHA
            // Os parâmetros da função adiciona_direita são: o nó r, a pos onde o novo código deveria ser inserido
            // pt_dados indicando os dados relacionados ao código no arquivo de dados
            // p = -1 quando é uma folha, pois os filhos são sempre nulos, no caso de arquivo "-1"
            adiciona_direita(r, pos, codigo, pt_dados, -1);

            // Após ter feito o deslocamento e inserção, escreve o nó atualizado no arquivo
            escreve_no(files.file_indices, r, pos_atual);
        } else{
            // O trecho de código abaixo é responsável por fazer a inserção a partir de um nó interno
            ARVOREB * filho = ler_no(files.file_indices, r->filho[pos]);
            cadastrar_aux(files, filho, codigo, pt_dados, r->filho[pos], cab_indices);

            if( overflow(filho) ){
                int meio, pos_meio, posicao_no_pos_split;

                posicao_no_pos_split = split(files, filho, r->filho[pos], &meio, &pos_meio, cab_indices);
                adiciona_direita(r, pos, meio, pos_meio, posicao_no_pos_split);
                escreve_no(files.file_indices, r, pos_atual);
                escreve_cabecalho_indices(files.file_indices, cab_indices);
            }

            free(filho);
        }
    }
}

