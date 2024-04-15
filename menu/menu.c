#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../insercao/produto_insercao.h"
#include "../impressao/produto_impressao.h"
#include "../remocao/produto_remocao.h"
#include "../atualizacao/produto_atualizacao.h"

// Exibe o cabeçalho do menu
// Pré-condições: Nenhuma
// Pós-condição: O cabeçalho do menu é exibido no console
void header_menu(){
    printf("\nMenu:\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Remover Produto\n");
    printf("3. Atualizar Preco\n");
    printf("4. Atualizar Estoque\n");
    printf("5. Imprimir Informacoes de um Produto\n");
    printf("6. Imprimir Lista de Todos os Produtos\n");
    printf("7. Imprimir Arvore\n");
    printf("8. Imprimir Lista de Livres do Arquivo de Indices\n");
    printf("9. Imprimir Lista de Livres do Arquivo de Dados\n");
    printf("10. Realizar Operacoes em Lote\n");
    printf("11. Imprimir infos dos nós\n");
    printf("0. Sair\n");
}

// Cadastra um novo produto
// Pré-condições: Nenhuma
// Pós-condição: Um novo produto é cadastrado
void cadastrarProduto(ARQUIVOS files) {
    printf("---> Operacao: Cadastrar Produto\n");
    cadastrar_produto(files);
    // Implemente a lógica para cadastrar um produto
}

// Remove um produto existente
// Pré-condições: Nenhuma
// Pós-condição: O produto é removido do cadastro
void removerProduto(ARQUIVOS files) {
    printf("---> Operacao: Remover Produto\n");
    remover_produto(files);
    // Implemente a lógica para remover um produto
}

// Atualiza o preço de um produto
// Pré-condições: Nenhuma
// Pós-condição: O preço do produto é atualizado
void atualizarPreco(ARQUIVOS files) {
    // Implemente a lógica para atualizar o preço de um produto
    printf("---> Operacao: Atualizar Preco\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if( cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("Digite o codigo do produto de preco a ser atualizado:\n");
        scanf("%d", &cod);
        atualizar_preco_produto(files, cod);
    }
    free(cab_indices);
}

// Atualiza o estoque de um produto
// Pré-condições: Nenhuma
// Pós-condição: O estoque do produto é atualizado
void atualizarEstoque(ARQUIVOS files) {
    printf("---> Operacao: Atualizar Estoque\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int cod;
        printf("Digite o codigo do produto de estoque a ser atualizado:\n");
        scanf("%d", &cod);
        atualizar_estoque_produto(files, cod);
    }
    free(cab_indices);
}

// Imprime as informações de um produto específico
// Pré-condições: Nenhuma
// Pós-condição: As informações do produto são impressas no console
void imprimirInformacoes(ARQUIVOS files) {
    printf("---> Operacao: Imprimir informacoes de um produto\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        int codigo;
        printf("Digite o código desejado para busca-lo: ");
        scanf("%d", &codigo);
        imprimir_informacoes_produto(files, codigo);
    }
    free(cab_indices);
}

// Imprime a lista de todos os produtos cadastrados
// Pré-condições: Nenhuma
// Pós-condição: A lista de todos os produtos é impressa no console
void imprimirListaProdutos(ARQUIVOS files) {
    printf("Operacao: Imprimir Lista de Produtos\n\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1) {
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    }else {
        imprimir_lista_produtos(files, cab_indices->pos_raiz);
    }
    free(cab_indices);
}

// Imprime a árvore de produtos
// Pré-condições: Nenhuma
// Pós-condição: A árvore de produtos é impressa no console
void imprimirArvore(ARQUIVOS files) {
    // Implemente a lógica para imprimir a árvore de produtos
    printf("---> Operacao: Imprimir Arvore\n");
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_raiz == -1){
        printf("---> A arvore esta vazia, nao e possivel realizar a operacao!\n");
    } else {
        imprimir_arvore(files);
    }

    free(cab_indices);
}

// Imprime a lista de nós livres do arquivo de índices
// Pré-condições: Nenhuma
// Pós-condição: A lista de nós livres do arquivo de índices é impressa no console
void imprimirListaLivresIndices() {
    printf("Operacao: Imprimir Lista de Livres do Arquivo de Indices\n");
    // Implemente a lógica para imprimir a lista de livres do arquivo de índices
}

// Imprime a lista de registros livres do arquivo de dados
// Pré-condições: Nenhuma
// Pós-condição: A lista de registros livres do arquivo de dados é impressa no console
void imprimirListaLivresDados() {
    printf("Operacao: Imprimir Lista de Livres do Arquivo de Dados\n");
    // Implemente a lógica para imprimir a lista de livres do arquivo de dados
}

// Realiza operações em lote a partir de um arquivo de texto
// Pré-condições: O arquivo de texto contendo as operações em lote deve existir e estar formatado corretamente
// Pós-condição: As operações em lote são executadas
void realizarOperacoesEmLote() {
    printf("Operacao: Realizar Operacoes em Lote\n");
    // Implemente a lógica para realizar operações em lote
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

// Exibe o menu principal e processa a escolha do usuário
// Pré-condições: Nenhuma
// Pós-condição: O usuário escolhe uma opção do menu e a operação correspondente é executada
void menu_principal(ARQUIVOS files){
    int opcao;

    do {
        header_menu();
        printf("Escolha uma opcao: ");
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
