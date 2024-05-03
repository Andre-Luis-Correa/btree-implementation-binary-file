#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "produto_insercao.h"
#include "produto_impressao.h"
#include "produto_remocao.h"
#include "produto_atualizacao.h"
#include "lote.h"

// Exibe o cabeçalho do menu
// Pré-condições: Nenhuma
// Pós-condições: O cabeçalho do menu é exibido no console
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
    printf("| 0. Sair                                          |\n");
    printf("+--------------------------------------------------+\n");
}


// Cadastra um novo produto
// Pré-condições: Nenhuma
// Pós-condições: Um novo produto é cadastrado
void cadastrarProduto(ARQUIVOS files) {
    printf("\n---> Operacao: Cadastrar Produto\n");
    cadastrar_produto(files);
}

// Remove um produto existente
// Pré-condições: O produto a ser removido deve existir no cadastro
// Pós-condições: O produto é removido do cadastro
void removerProduto(ARQUIVOS files) {
    printf("\n---> Operacao: Remover Produto\n");
    remover_produto(files);
}

// Atualiza o preço de um produto
// Pré-condições: O produto a ser atualizado deve existir no cadastro
// Pós-condições: O preço do produto é atualizado
void atualizarPreco(ARQUIVOS files) {
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
// Pré-condições: O produto a ser atualizado deve existir no cadastro
// Pós-condições: O estoque do produto é atualizado
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

// Imprime as informações de um produto específico
// Pré-condições: O produto cujas informações serão impressas deve existir no cadastro
// Pós-condições: As informações do produto são impressas no console
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
// Pré-condições: Nenhuma
// Pós-condições: A lista de todos os produtos é impressa no console
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

// Imprime a árvore de produtos
// Pré-condições: Nenhuma
// Pós-condições: A árvore de produtos é impressa no console
void imprimirArvore(ARQUIVOS files) {
    printf("\n---> Operacao: Imprimir Arvore\n");
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
// Pós-condições: A lista de nós livres do arquivo de índices é impressa no console
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
// Pré-condições: Nenhuma
// Pós-condições: A lista de registros livres do arquivo de dados é impressa no console
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

// Realiza operações em lote a partir de um arquivo de texto
// Pré-condições: O arquivo de texto contendo as operações em lote deve existir e estar formatado corretamente
// Pós-condições: As operações em lote são executadas
void realizarOperacoesEmLote(ARQUIVOS files) {
    printf("\n---> Operacao: Realizar Operacoes em Lote\n");
    printf("\n---> Digite o nome do arquivo com extensao (.txt): ");

    char file[MAX_NOME];
    scanf("%s", file);

    ler_arquivo(files, file);
}

// Exibe o menu principal e processa a escolha do usuário
// Pré-condições: Nenhuma
// Pós-condições: O usuário escolhe uma opção do menu e a operação correspondente é executada
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
            case 0:
                printf("---> Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("---> Opcao invalida! Escolha uma opcao valida.\n");
        }
    } while (opcao != 0);

}