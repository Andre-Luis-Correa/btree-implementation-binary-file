//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto_insercao.h"
#include "../impressao/produto_impressao.h"

// Função para ler os dados de um produto
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

int overflow (ARVOREB * r){
    return r->num_chaves == ORDEM;
}

int eh_folha(ARVOREB * r){
    return r->filho[0] == -1;
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
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fwrite (no, sizeof (ARVOREB), 1, file_indices);
}

// Função para ler um registro de dados de um produto no arquivo de dados
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos){
    DADOS_REGISTRO * registro = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO));
    fseek (file_dados, sizeof (CABECALHO_DADOS) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
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
            printf("%d    e   %d\n", codigo, r->chave[i]);
            printf("\nPos: %d\n", pos);
            free(r);
            return pos;
        } else if (r->chave[i] > codigo ){
            int pos_atual = r->filho[i];
            free(r);
            return buscar_no(file_indices, codigo, pos_atual);
        }
    }
    int pos_atual = r->filho[i];
    free(r);
    return buscar_no(file_indices, codigo, pos_atual);
}

void imprimir_cabecalho_indices(CABECALHO_INDICES * cab){
    printf("\nCABECALHO DE INDICES: raiz: %d topo: %d livre: %d\n", cab->pos_raiz, cab->pos_topo, cab->pos_livre);
}

void imprimir_cabecalho_dados(CABECALHO_DADOS * cab){
    printf("\nCABECALHO DE DADOS: topo: %d livre: %d\n", cab->pos_topo, cab->pos_livre);
}

void cadastrar_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);

    imprimir_cabecalho_indices(cab_indices);
    imprimir_cabecalho_dados(cab_dados);

    PRODUTO_DATA * produto = ler_produto();

    if(buscar_no(files.file_indices, produto->codigo, cab_indices->pos_raiz) == -1){
        // Realizar a inserção do nó, pois ainda não existe esse código na árvore
        printf("\nNova insercao!\n");
        cadastrar_produto_files(files, produto);
    }else{
        printf("\nATENCAO: Codigo de produto ja existente!\n");
    }

    free(cab_indices);
    free(produto);
}

void cadastrar_produto_files(ARQUIVOS files, PRODUTO_DATA * produto) {
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_livre == -1) {
        printf("A inserção sera feita considerando que nao ha nos livres!\n");
        cadastrar_produto_sem_nos_livres(files, produto, cab_indices->pos_raiz);
    } else {
        printf("A inserção sera feita considerando que ha nos livres!\n");
        cadastrar_produto_com_nos_livres(files, produto, cab_indices->pos_raiz);
    }

    free(cab_indices);
}

void cria_no(ARVOREB * r, int codigo, int pos_dados) {
    r->chave[0] = codigo;
    r->num_chaves = 1;
    r->prox_livre = -1;
    r->pt_dados[0] = pos_dados;
    for(int i = 0; i <= r->num_chaves; i++)
        r->filho[i] = -1;
}

void cria_registro(DADOS_REGISTRO * dados, PRODUTO_DATA * produto){
    dados->produto = *produto;
    dados->prox_livre = -1;
}

int split (ARQUIVOS files, ARVOREB * x, int pos, int * meio, int * pos_meio, CABECALHO_INDICES * cab_indices){
    ARVOREB* y = (ARVOREB*) malloc (sizeof(ARVOREB));

    // O q representa o a metade do nó
    int q = x->num_chaves/2;
    y->num_chaves = x->num_chaves - q - 1;
    x->num_chaves = q;

    printf("\n----> Antes de escrever: ");
    ARVOREB * teste = ler_no(files.file_indices, 1);
    imprimir_no(teste);
    free(teste);

    escreve_no(files.file_indices, x, pos);

    printf("\n----> DEPOISde escrever: ");
    teste = ler_no(files.file_indices, 1);
    imprimir_no(teste);
    free(teste);

    *meio = x->chave[q];
    *pos_meio = x->pt_dados[q];
    int i;
    y->filho[0] = x->filho[q+1];
    for (i = 0 ; i < y->num_chaves ; i++){
        y->chave[i] = x->chave[q+i+1];
        y->pt_dados[i] = x->pt_dados[q+i+1];
        y->filho[i+1] = x->filho[q+i+2];
    }

    //CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    printf("Antes do split: ");
    imprimir_cabecalho_indices(cab_indices);
    int pos_y = cab_indices->pos_topo;
    printf("\nEssa e a pos_y: %d\n", pos_y);
    escreve_no(files.file_indices, y, cab_indices->pos_topo);
    cab_indices->pos_topo++;
    printf("Esse e o novo topo: %d\n", cab_indices->pos_topo);
    escreve_cabecalho_indices(files.file_indices, cab_indices);
    printf("Depois do split: ");
    imprimir_cabecalho_indices(cab_indices);
    //free(cab_indices);
    return pos_y;
}

void cadastrar_produto_sem_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    ARVOREB * r = (ARVOREB*) malloc(sizeof (ARVOREB));
    DADOS_REGISTRO * dados = (DADOS_REGISTRO *) malloc(sizeof (DADOS_REGISTRO));

    imprimir_cabecalho_indices(cab_indices);
    imprimir_cabecalho_dados(cab_dados);

    if (pos == -1) { // pos -> pos_raiz == -1 árvore vazia ou a função recebeu uma posição (pos) vazia
        printf("-> Insercao em arvore vazia!");

        // Atualiza a poisção da cabeça
        cab_indices->pos_raiz = 0;

        // Escreve no arquivo de dados as informações do produto a ser inserido
        cria_registro(dados, produto);
        escreve_registro(files.file_dados, dados, cab_dados->pos_topo);

        // Cria a raiz com as informações: código do produto e o ponteiro de dados do arquivo de dados
        cria_no(r, produto->codigo, cab_dados->pos_topo);
        escreve_no(files.file_indices, r, cab_indices->pos_topo);

        // Atualiza os cabeçalhos de AMBOS arquivos
        cab_indices->pos_topo++;
        cab_dados->pos_topo++;
        escreve_cabecalho_indices(files.file_indices, cab_indices);
        escreve_cabecalho_dados(files.file_dados, cab_dados);

        // Teste: Imprimir cabeçalhos para visualizar a atualização que ocorreu
        imprimir_cabecalho_indices(cab_indices);
        imprimir_cabecalho_dados(cab_dados);
    } else { // árvore não vazia

        printf("-> Insercao em arvore com elementos!\n");

        // Lê a raiz da árvore
        ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);

        // Cria um registro e escreve no arquivo de dados
        DADOS_REGISTRO * dados_novos = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO));
        cria_registro(dados_novos, produto);
        escreve_registro(files.file_dados, dados_novos, cab_dados->pos_topo);

        // Guarda a informação de onde o novo registro foi inserido no arquivo de dados
        int pt_dados_atual = cab_dados->pos_topo;

        // Atualiza o cabecalho do ARQUIVO de DADOS
        cab_dados->pos_topo++;
        escreve_cabecalho_dados(files.file_dados, cab_dados);

        // Chama a função auxiliar de inserção
        // Os parâmetros são: Os arquivos (AMBOS), código do produto, ponteiro de dado do produto, posição da raiz
        cadastrar_aux (files, raiz, produto->codigo, pt_dados_atual, cab_indices->pos_raiz);

        // Lê o cabeçalho atual do arquivo de índices
        CABECALHO_INDICES * cab_indices_atual = le_cabecalho_indices(files.file_indices);
        imprimir_cabecalho_indices(cab_indices_atual);

        if(overflow(raiz)){
            printf("\n Essa e a raiz pre split: ");
            imprimir_no(raiz);
            int meio;

            printf("\n--------------> Overflow na função CADASTRAR SEM NOS LIVRES\n");
            int pos_meio;
            int arvore_x = split(files, raiz, cab_indices_atual->pos_raiz, &meio, &pos_meio, cab_indices_atual);

            printf("\n Essa e a raiz pos split: ");
            imprimir_no(raiz);
            ARVOREB * teste_x = (ARVOREB*) malloc(sizeof (ARVOREB));
            teste_x = ler_no(files.file_indices, arvore_x);
            printf("\n Esse e a no criado a partir do split: ");
            imprimir_no(teste_x);

            ARVOREB * nova_raiz = (ARVOREB*) malloc(sizeof (ARVOREB));
            nova_raiz->chave[0] = meio;
            nova_raiz->pt_dados[0] = pos_meio;
            nova_raiz->filho[0] = cab_indices_atual->pos_raiz;
            nova_raiz->filho[1] = arvore_x;
            for (int i = (((int) ORDEM/2) +1) ; i < ORDEM ; i++){
                raiz->filho[i] = -1;
            }
            nova_raiz->num_chaves = 1;

            printf("\nEssa e a nova raiz: ");
            imprimir_no(nova_raiz);

            escreve_no(files.file_indices, nova_raiz, cab_indices_atual->pos_topo);
            cab_indices_atual->pos_raiz = cab_indices_atual->pos_topo;
            printf("\nPosicao da nova raiz: %d\n", cab_indices_atual->pos_topo);

            cab_indices_atual->pos_topo++;

            printf("\nPosicao da novo topo: %d\n", cab_indices_atual->pos_topo);

            escreve_cabecalho_indices(files.file_indices, cab_indices_atual);
            printf("\nImprimir cabecalho pos split: ");
            imprimir_cabecalho_indices(cab_indices_atual);
            free(nova_raiz);
            free(teste_x);
        }
        free(raiz);
        free(cab_indices_atual);
    }

    free(r);
    free(dados);
    free(cab_indices);
    free(cab_dados);
    printf("\nInsercao realizada com sucesso!\n");
}

int busca_pos (ARVOREB * r, int codigo, int * pos){
    // O loop busca pela posição onde a nova chave (codigo) deveria entrar
    for ((*pos) = 0 ; (*pos) < r->num_chaves ; (*pos)++){
        if (codigo == r->chave[(*pos)]){
            printf("\nO codigo %d é igual a chave %d. E a pos é: %d\n", codigo, r->chave[*pos], *pos);
            return 1;
        }
        else if (codigo < r->chave[(*pos)]){
            printf("\nO codigo %d é menor que a chave %d. E a pos é: %d\n", codigo, r->chave[*pos], *pos);
            break;
        }
    }

    printf("\nO codigo %d é maior que a chave %d. E a pos é: %d\n", codigo, r->chave[*pos], *pos);
    return 0;
}

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

// Os parâmetros são: Os arquivos (AMBOS), código do produto, ponteiro de dado do produto, posição da raiz (Na 1° chamada)
void cadastrar_aux(ARQUIVOS files, ARVOREB * r, int codigo, int pt_dados, int pos_atual){
    // Variável para armazenar a posiçao na qual uma determinada chave deveria entrar
    int pos;
    CABECALHO_INDICES  *  cab_indices = (CABECALHO_INDICES*) malloc(sizeof (CABECALHO_INDICES));
    cab_indices = le_cabecalho_indices(files.file_indices);

    if(!busca_pos(r, codigo, &pos)){
        // O trecho de código abaixo é responsável por printar a pos encontrada e o nó analisado em relação a essa pos
        printf("Essa e a pos: %d para o codigo: %d\n", pos, codigo);
        imprimir_no(r);
        // A função eh-folha verifica se o nó r é folha
        if (eh_folha(r)){
            // Caso o nó seja uma folha a inserção é feita nele mesmo: EM UMA ÁRVORE B A INSERÇÃO É SEMPRE NA FOLHA
            // Os parâmetros da função adiciona_direita são: o nó r, a pos onde o novo código deveria ser inserido
            // pt_dados indicando os dados relacionados ao código no arquivo de dados
            // p = -1 quando é uma folha, pois os filhos são sempre nulos, no caso de arquivo "-1"
            adiciona_direita(r, pos, codigo, pt_dados, -1);

            // Teste: Essa immpressão é somente para teste para verificar se o nó R realmente foi atualizado
            imprimir_no(r);

            // Após ter feito o deslocamento e inserção, escreve o nó atualizado no arquivo
            escreve_no(files.file_indices, r, pos_atual);
        } else{
            // O trecho de código abaixo é responsável por fazer a inserção a partir de um nó interno
            ARVOREB * filho= ler_no(files.file_indices, r->filho[pos]);
            cadastrar_aux(files, filho, codigo, pt_dados, r->filho[pos]);

            if(overflow(filho)){
                printf("\nFILHOOOOOOO\n");
                ARVOREB  * teste = ler_no(files.file_indices, 1);
                imprimir_no(teste);

                printf("\nOverflow na função CADASTRAR AUX\n");
                int meio;
                int pos_meio;

                printf("\nEsse e o nó filho antes do split:");
                imprimir_no(filho);

                int posicao_no_pos_split = split(files, filho, r->filho[pos], &meio, &pos_meio, cab_indices);
                teste = ler_no(files.file_indices, 1);
                imprimir_no(teste);
                escreve_no(files.file_indices, filho, r->filho[pos]);

                teste = ler_no(files.file_indices, 1);
                imprimir_no(teste);

                printf("\nEsse e o nó filho depois do split:");
                imprimir_no(filho);

                printf("\nEsse e o nó criado pelo split:");
                ARVOREB * novo_no = ler_no(files.file_indices, posicao_no_pos_split);
                imprimir_no(novo_no);

                printf("\n");
                imprimir_cabecalho_indices(cab_indices);
                printf("\n--------> POS para chamar adiciona direita: %d\n", pos);
                adiciona_direita(r, pos, meio, pos_meio, posicao_no_pos_split);

                teste = ler_no(files.file_indices, 1);
                imprimir_no(teste);

                printf("\nEsse e a nova raiz (r) pos split:");
                imprimir_no(r);
                printf("\n--------> POS RAIZ ATUAL : %d\n", pos_atual);
                escreve_no(files.file_indices, r, pos_atual);

                escreve_cabecalho_indices(files.file_indices, cab_indices);
            }
            free(filho);
        }
    }
}

void cadastrar_produto_com_nos_livres(ARQUIVOS files, PRODUTO_DATA * produto, int pos){

}

