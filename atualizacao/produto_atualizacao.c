//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_atualizacao.h"
#include "../insercao/produto_insercao.h"

void atualizar_preco_produto(ARQUIVOS files, int codigo_produto){
    //lendo os cabecalhos de indices e file_dados
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);

    imprimir_cabecalho_indices(cab_indices);
    imprimir_cabecalho_dados(cab_dados);

    //a pos esta guarando o no em que esta elemento que possui esse codigo de produto
    int pos = buscar_no(files.file_indices, codigo_produto, cab_indices->pos_raiz);

    if (pos == -1) {
        printf("Produto com código %d não encontrado.\n", codigo_produto);
        return;
    }

    ARVOREB * no = ler_no(files.file_indices, pos);

    // procurar o indice do codigo dentro do nó
    int indice = -1;
    for (int i = 0; i < no->num_chaves; i++) {
        if (no->chave[i] == codigo_produto) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Produto com código %d não encontrado.\n", codigo_produto);
        return;
    }
    // ler o registro de dados do produto
    DADOS_REGISTRO * registro = ler_registro(files.file_dados, no->pt_dados[indice]);

    // atualizar o preco do produto
    float novo_preco;
    printf("Insira o novo preço para o produto de código %d: ", codigo_produto);
    scanf("%f", &novo_preco);
    registro->produto.preco = novo_preco;

    // Escrever o registro atualizado de volta no arquivo de dados
    escreve_registro(files.file_dados, registro, no->pt_dados[indice]);

    // Liberar memória alocada
    free(no);
    free(registro);

    printf("Preço do produto com código %d atualizado com sucesso.\n", codigo_produto);
    free(cab_indices);
}

// Função para atualizar o estoque de um produto a partir do seu código
void atualizar_estoque(ARQUIVOS files, int codigo_produto) {
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);

    imprimir_cabecalho_indices(cab_indices);
    imprimir_cabecalho_dados(cab_dados);

    int pos = buscar_no(files.file_indices, codigo_produto, cab_indices->pos_raiz);

    if (pos == -1) {
        printf("Produto com código %d não encontrado.\n", codigo_produto);
        return;
    }

    ARVOREB * no = ler_no(files.file_indices, pos);

    // Procurar o índice do código dentro do nó
    int indice = -1;
    for (int i = 0; i < no->num_chaves; i++) {
        if (no->chave[i] == codigo_produto) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Produto com código %d não encontrado.\n", codigo_produto);
        return;
    }

    // Ler o registro de dados do produto
    DADOS_REGISTRO * registro = ler_registro(files.file_dados, no->pt_dados[indice]);

    // Atualizar o estoque do produto
    int novo_estoque;
    printf("Insira o novo estoque para o produto de código %d: ", codigo_produto);
    scanf("%d", &novo_estoque);
    registro->produto.estoque = novo_estoque;

    // Escrever o registro atualizado de volta no arquivo de dados
    escreve_registro(files.file_dados, registro, no->pt_dados[indice]);

    // Liberar memória alocada
    free(no);
    free(registro);

    printf("Estoque do produto com código %d atualizado com sucesso.\n", codigo_produto);
    free(cab_indices);
    free(cab_dados);
}