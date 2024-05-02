#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"
#include "../remocao/produto_remocao.h"
#include "../atualizacao/produto_atualizacao.h"
#include "../utils/arvore_utils.h"
#include "../lote/lote.h"

// Exibe o cabe?alho do menu
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O cabe?alho do menu ? exibido no console
void header_menu(){
    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("|                     Menu:                        |\n");
    printf("+--------------------------------------------------+\n");
    printf("| 1. Cadastrar Produto                             |\n");
    printf("| 2. Remover Produto                               |\n");
    printf("| 3. Atualizar Preco                               |\n");
    printf("| 4. Atualizar Estoque                             |\n");
    printf("| 5. Imprimir Informacoes de um Produto            |\n");
    printf("| 6. Imprimir Lista de Todos os Produtos           |\n");
    printf("| 7. Imprimir Arvore                               |\n");
    printf("| 8. Imprimir Lista de Livres do Arquivo de Indices|\n");
    printf("| 9. Imprimir Lista de Livres do Arquivo de Dados  |\n");
    printf("| 10. Realizar Operacoes em Lote                   |\n");
    printf("| 11. Imprimir infos dos nos                       |\n");
    printf("| 0. Sair                                          |\n");
    printf("+--------------------------------------------------+\n");
}


// Cadastra um novo produto
// Pr?-condi??es: Nenhuma
// P?s-condi??o: Um novo produto ? cadastrado
void cadastrarProduto(ARQUIVOS files) {
    printf("\n---> Operacao: Cadastrar Produto\n");
    cadastrar_produto(files);
    // Implemente a l?gica para cadastrar um produto
}

// Remove um produto existente
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O produto ? removido do cadastro
void removerProduto(ARQUIVOS files) {
    printf("\n---> Operacao: Remover Produto\n");
    remover_produto(files);
    // Implemente a l?gica para remover um produto
}

// Atualiza o pre?o de um produto
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O pre?o do produto ? atualizado
void atualizarPreco(ARQUIVOS files) {
    // Implemente a l?gica para atualizar o pre?o de um produto
    printf("\n---> Operacao: Atualizar Preco\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if( cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("---> Digite o codigo do produto a ser atualizado:");
        scanf("%d", &cod);
        float novo_preco;
        printf("\n---> Insira o novo preco: ");
        scanf("%f", &novo_preco);

        atualizar_preco_produto(files, cod, novo_preco);
    }
    free(cab_indices);
}

// Atualiza o estoque de um produto
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O estoque do produto ? atualizado
void atualizarEstoque(ARQUIVOS files) {
    printf("\n---> Operacao: Atualizar Estoque\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("---> Digite o codigo do produto de estoque a ser atualizado:");
        scanf("%d", &cod);
        int novo_estoque;
        printf("\n---> Insira o novo estoque");
        scanf("%d", &novo_estoque);
        atualizar_estoque_produto(files, cod, novo_estoque);
    }
    free(cab_indices);
}

// Imprime as informa??es de um produto espec?fico
// Pr?-condi??es: Nenhuma
// P?s-condi??o: As informa??es do produto s?o impressas no console
void imprimirInformacoes(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir informacoes de um produto\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int codigo;
        printf("---> Digite o codigo desejado para busca-lo: ");
        scanf("%d", &codigo);
        imprimir_informacoes_produto(files, codigo);
    }
    free(cab_indices);
}

// Imprime a lista de todos os produtos cadastrados
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A lista de todos os produtos ? impressa no console
void imprimirListaProdutos(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir Lista de Produtos\n\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1) {
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    }else {
        printf("+-------------------------------------------------------------------------------------------------------------------+\n");
        printf("|                                                 Lista de Produtos                                                 |\n");
        printf("+-------------------------------------------------------------------------------------------------------------------+\n");
        printf("| CODIGO   | NOME                                               | MARCA                     | ESTOQUE  | PRECO      |\n");
        printf("+-------------------------------------------------------------------------------------------------------------------+\n");
        imprimir_lista_produtos(files, cab_indices->pos_raiz);
        printf("+-------------------------------------------------------------------------------------------------------------------+\n");
    }
    free(cab_indices);
}

// Imprime a ?rvore de produtos
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A ?rvore de produtos ? impressa no console
void imprimirArvore(ARQUIVOS files) {
    // Implemente a l?gica para imprimir a ?rvore de produtos
    printf("\n---> Operacao: Imprimir Arvore\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        imprimir_arvore(files);
    }

    free(cab_indices);
}

// Imprime a lista de n?s livres do arquivo de ?ndices
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A lista de n?s livres do arquivo de ?ndices ? impressa no console
void imprimirListaLivresIndices(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir Lista de Livres do Arquivo de Indices\n");
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (cab_indices->pos_raiz == -1) {
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else if(cab_indices->pos_livre == -1) {
        printf("---> Nao ha posicoes com indices livres!\n");
    } else {
        imprimir_lista_indices_livres(files.file_indices, cab_indices->pos_livre);
    }

    free(cab_indices);
}

// Imprime a lista de registros livres do arquivo de dados
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A lista de registros livres do arquivo de dados ? impressa no console
void imprimirListaLivresDados(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir Lista de Livres do Arquivo de Dados\n");
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else if(cab_dados->pos_livre == -1 ) {
        printf("---> Nao ha posicoes com registros de dados livres!\n");
    } else {
        imprimir_lista_registros_livres(files.file_dados, cab_dados->pos_livre);
    }
    free(cab_dados);
}

// Realiza opera??es em lote a partir de um arquivo de texto
// Pr?-condi??es: O arquivo de texto contendo as opera??es em lote deve existir e estar formatado corretamente
// P?s-condi??o: As opera??es em lote s?o executadas
void realizarOperacoesEmLote(ARQUIVOS files) {
    printf("\n---> Operacao: Realizar Operacoes em Lote\n");
    printf("\n---> Digite o nome do arquivo com extensao (.txt): ");

    char file[MAX_NOME];
    scanf("%s", file);

    ler_arquivo(files, file);
}

void imprimir_info_nos(ARQUIVOS files){
    printf("\n----> Operacao: Impressao de infos no no: \n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        imprimir_info_nos_chaves(files, cab_indices->pos_raiz);
    }

    free(cab_indices);
}

void buscar(ARQUIVOS files){
    printf("\n----> Operacao: BUscar pai: \n");
    int codigo;

    printf("\n---> Digite o valor para buscar o no pai: ");
    scanf("%d", &codigo);

    int pos_pai = buscar_pai_by_pos(files.file_indices, codigo);
    printf("\n POS PAI : %d", pos_pai);
    ARVOREB * pai = ler_no(files.file_indices, pos_pai);
    if(pai != NULL)
        imprimir_no(pai);
    else
        printf("\n---> Ta nulo!");
    free(pai);
}

void buscar_pos_no(ARQUIVOS files){
    printf("\n----> Operacao: BUscar pos no: \n");
    int codigo;

    printf("\n---> Digite o valor para buscar a pos do no: ");
    scanf("%d", &codigo);

    int pos_pai = buscar_no(files.file_indices, codigo);
    printf("\n POS no : %d", pos_pai);
    ARVOREB * no = ler_no(files.file_indices, pos_pai);
    if(no != NULL)
        imprimir_no(no);
    else
        printf("\n---> Ta nulo!");
    free(no);
}

// Exibe o menu principal e processa a escolha do usu?rio
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O usu?rio escolhe uma op??o do menu e a opera??o correspondente ? executada
void menu_principal(ARQUIVOS files){
    int opcao;

    do {
        header_menu();
        printf("\n--> Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(files);
                break;
            case 2:
                removerProduto(files);
                break;
            case 3:
                atualizarPreco(files);
                break;
            case 4:
                atualizarEstoque(files);
                break;
            case 5:
                imprimirInformacoes(files);
                break;
            case 6:
                imprimirListaProdutos(files);
                break;
            case 7:
                imprimirArvore(files);
                break;
            case 8:
                imprimirListaLivresIndices(files);
                break;
            case 9:
                imprimirListaLivresDados(files);
                break;
            case 10:
                realizarOperacoesEmLote(files);
                break;
            case 11:
                imprimir_info_nos(files);
                break;
            case 12:
                buscar(files);
                break;
            case 13:
                buscar_pos_no(files);
                break;
            case 0:
                printf("---> Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("---> Opcao invalida! Escolha uma opcao valida.\n");
        }
    } while (opcao != 0);

    return;
}