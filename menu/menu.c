#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"
#include "../remocao/produto_remocao.h"
#include "../atualizacao/produto_atualizacao.h"

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
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("---> Digite o codigo do produto de preco a ser atualizado:\n");
        scanf("%d", &cod);
        atualizar_preco_produto(files, cod);
    }
    free(cab_indices);
}

// Atualiza o estoque de um produto
// Pr?-condi??es: Nenhuma
// P?s-condi??o: O estoque do produto ? atualizado
void atualizarEstoque(ARQUIVOS files) {
    printf("\n---> Operacao: Atualizar Estoque\n");
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("---> Digite o codigo do produto de estoque a ser atualizado:\n");
        scanf("%d", &cod);
        atualizar_estoque_produto(files, cod);
    }
    free(cab_indices);
}

// Imprime as informa??es de um produto espec?fico
// Pr?-condi??es: Nenhuma
// P?s-condi??o: As informa??es do produto s?o impressas no console
void imprimirInformacoes(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir informacoes de um produto\n");
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1){
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
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1) {
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    }else {
        printf("+----------------------------------------------------------------------------------------------+\n");
        printf("|                                         Lista de Produtos                                    |\n");
        printf("+----------------------------------------------------------------------------------------------+\n");
        printf("| CODIGO   | NOME                           | MARCA                     | ESTOQUE  | PRECO     |\n");
        printf("+----------------------------------------------------------------------------------------------+\n");
        imprimir_lista_produtos(files, cab_indices->posRaiz);
        printf("+----------------------------------------------------------------------------------------------+\n");
    }
    free(cab_indices);
}

// Imprime a ?rvore de produtos
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A ?rvore de produtos ? impressa no console
void imprimirArvore(ARQUIVOS files) {
    // Implemente a l?gica para imprimir a ?rvore de produtos
    printf("\n---> Operacao: Imprimir Arvore\n");
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        imprimir_arvore(files);
    }

    free(cab_indices);
}

// Imprime a lista de n?s livres do arquivo de ?ndices
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A lista de n?s livres do arquivo de ?ndices ? impressa no console
void imprimirListaLivresIndices() {
    printf("\n---> Operacao: Imprimir Lista de Livres do Arquivo de Indices\n");
    // Implemente a l?gica para imprimir a lista de livres do arquivo de ?ndices
}

// Imprime a lista de registros livres do arquivo de dados
// Pr?-condi??es: Nenhuma
// P?s-condi??o: A lista de registros livres do arquivo de dados ? impressa no console
void imprimirListaLivresDados() {
    printf("\n---> Operacao: Imprimir Lista de Livres do Arquivo de Dados\n");
    // Implemente a l?gica para imprimir a lista de livres do arquivo de dados
}

// Realiza opera??es em lote a partir de um arquivo de texto
// Pr?-condi??es: O arquivo de texto contendo as opera??es em lote deve existir e estar formatado corretamente
// P?s-condi??o: As opera??es em lote s?o executadas
void realizarOperacoesEmLote() {
    printf("\n---> Operacao: Realizar Operacoes em Lote\n");
    // Implemente a l?gica para realizar opera??es em lote
}

void imprimir_info_nos(ARQUIVOS files){
    printf("\n----> Operacao: Impressao de infos no no: \n");
    CABECALHO_INDICES * cab_indices = lerCabecalhoIndices(files.fileIndices);

    if(cab_indices->posRaiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        imprimir_info_nos_chaves(files, cab_indices->posRaiz);
    }

    free(cab_indices);
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
                imprimirListaLivresIndices();
                break;
            case 9:
                imprimirListaLivresDados();
                break;
            case 10:
                realizarOperacoesEmLote();
                break;
            case 11:
                imprimir_info_nos(files);
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