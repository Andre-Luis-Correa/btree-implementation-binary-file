//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_insercao.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../cabecalho/cabecalho_dados.h"

// Função para ler os dados de um produto
PRODUTO_DATA * ler_produto() {
    PRODUTO_DATA * produto = (PRODUTO_DATA*) malloc(sizeof (PRODUTO_DATA));

    printf("\n--> CADASTRO DE PRODUTO: \n");
    printf("Insira o código do produto: ");
    scanf("%d", &produto->codigo);
    printf("Insira o nome do produto: ");
    scanf(" %[^\n]", produto->nome);
    printf("Insira a marca do produto: ");
    scanf(" %[^\n]", produto->marca);
    printf("Insira a categoria do produto: ");
    scanf(" %[^\n]", produto->categoria);
    printf("Insira a quantidade em estoque do produto: ");
    scanf("%d", &produto->estoque);
    printf("Insira o preço do produto: ");
    scanf("%f", &produto->preco);

    return produto;
}

// Função para imprimir os dados de um produto
void imprimir_produto(PRODUTO_DATA * produto) {
    printf("\nDados do Produto:\n");
    printf("Codigo: %d\n", produto->codigo);
    printf("Nome: %s\n", produto->nome);
    printf("Marca: %s\n", produto->marca);
    printf("Categoria: %s\n", produto->categoria);
    printf("Estoque: %d\n", produto->estoque);
    printf("Preco: R$ %.2f\n", produto->preco);
}

// Função para ler um nó do arquivo de índices da árvore B de produtos
ARVOREB * ler_no (FILE * file_indices, int pos){
    ARVOREB * no = (ARVOREB*) malloc(sizeof (ARVOREB));
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fread (no, sizeof (ARVOREB), 1, file_indices);
    return no;
}

// Função para escrever um nó no arquivo de índices
void escreve_no (FILE * file_indices, ARVOREB * no, int pos){
    fseek (file_indices, sizeof (CABECALHO_INDICES ) + pos * sizeof (ARVOREB), SEEK_SET);
    fwrite (no, sizeof (ARVOREB), 1, file_indices);
}

// Função para ler um registro de dados de um produto no arquivo de dados
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos){
    DADOS_REGISTRO * registro = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO));
    fseek (file_dados, sizeof (CABECALHO_DADOS ) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fread (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
    return registro;
}

// Função para escrever um nó no arquivo de índices
void escreve_registro (FILE * file_dados, DADOS_REGISTRO * registro, int pos){
    fseek (file_dados, sizeof (CABECALHO_DADOS ) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fwrite (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
}

// Função para verificar se já existe um determinado código na árvore e retorna a posição do mesmo
int buscar_no(FILE * file_indices, int codigo, int pos){
    //faz a busca no metodo árvore binaria de busca
    if(pos == -1) return -1;

    ARVOREB * r = ler_no(file_indices, pos);
    int i;

    for(i = 0; i < r->num_chaves; i++){
        if(r->chave[i] == codigo ){
            free(r);
            return pos;
        } else if (r->chave[i] > codigo ){
            return buscar_no(file_indices, codigo, r->filho[i]);
        }
    }

    return buscar_no(file_indices, codigo, r->filho[i]);
}

void imprimir_cabecalho_indices(CABECALHO_INDICES * cab){
    printf("\nCABECALHO DE INDICES: raiz: %d topo: %d livre: %d\n", cab->pos_raiz, cab->pos_topo, cab->pos_livre);
}

void cadastrar_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    imprimir_cabecalho_indices(cab_indices);

    PRODUTO_DATA * produto = ler_produto();
    imprimir_produto(produto);

    if(buscar_no(files.file_indices, produto->codigo, cab_indices->pos_raiz) == -1){
        // Realizar a inserção do nó, pois ainda não existe esse código na árvore
        printf("A insercao sera realizada considerando que nao ha nos livres\n");
        cadastrar_produto_files(files, produto);
    }else{
        printf("\nATENCAO: Codigo de produto ja existente!\n");
    }

    free(cab_indices);
    free(produto);
}

void cadastrar_produto_files(ARQUIVOS files, PRODUTO_DATA * produto) {
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_livre == -1) cadastrar_produto_sem_nos_livres(files, produto, cab_indices->pos_raiz);
    else cadastrar_produto_com_nos_livres(files, produto, cab_indices->pos_raiz);

    free(cab_indices);
}

void cria_no(ARVOREB * r, int codigo, int pos_dados) {
    r->chave[0] = codigo;
    r->num_chaves = 1;
    r->eh_folha = 0;
    r->prox_livre = -1;
    r->pt_dados[0] = pos_dados;
    for(int i = 0; i < ORDEM + 1; i++)
        r->filho[i] = -1;
}

void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto){
    dados->produto = *produto;
    dados->prox_livre = -1;
}

void cadastrar_produto_sem_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    ARVOREB * r = (ARVOREB*) malloc(sizeof (ARVOREB));
    DADOS_REGISTRO * dados = (DADOS_REGISTRO *) malloc(sizeof (DADOS_REGISTRO));

    if (pos == -1) { // pos -> pos_raiz == -1 árvore vazia ou a função recebeu uma posição (pos) vazia
        if (is_vazia_arvore_indices(cab_indices)){
            cab_indices->pos_raiz = 0;
        }
        cria_no(r, produto->codigo, cab_dados->pos_topo);
        escreve_no(files.file_indices, r, cab_indices->pos_topo);
        cria_registro(dados, produto);
        escreve_registro(files.file_dados, dados, cab_dados->pos_topo);
        cab_indices->pos_topo++;
        cab_dados->pos_topo++;
        escreve_cabecalho_indices(files.file_indices, cab_indices);
        escreve_cabecalho_dados(files.file_dados, cab_dados);
    } else { // árvore não vazia

        ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);
        cadastra_aux (files, raiz, produto);

    }

    free(r);
    free(raiz);
    free(dados);
    free(cab_indices);
    free(cab_dados);
}

int busca_pos (ARVOREB * r, int codigo, int * pos){
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

void adiciona_ireita (ARVOREB * r, int pos, int codigo, ARVOREB * p){
    int i;
    for (i = r->numChaves ; i > pos ; i--){
        r->chave [i] = r->chave[i-1];
        r->filho[i+1] = r->filho[i];
    }
    r->chave[pos] = codigo;
    r->filho[pos+1] = p;
    r->numChaves++;
}

void cadastra_aux(ARQUIVOS files, ARVOREB * r, PRODUTO_DATA * produto){
    int pos;

    if(!busca_pos(r, produto->codigo, &pos)){
        if (r->eh_folha){
            adiciona_direita(r, pos, produto->codigo, NULL);
        }
    }
}

void insere_aux (arvoreB * r, int info){
    int pos;
    if (!buscaPos (r, info, &pos)){
        if (eh_folha(r)){
            adicionaDireita(r, pos, info, NULL);
        }
        else{
            insere_aux(r->filho[pos], info);
            if (overflow(r->filho[pos])){
                int m;
                arvoreB* aux = split(r->filho[pos], &m);
                adicionaDireita(r, pos, m, aux);
            }
        }
    }
}

void cadastrar_produto_com_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos){

}