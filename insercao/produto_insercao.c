//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_insercao.h"


// Função para ler os dados de um produto
PRODUTO_DATA ler_produto() {
    PRODUTO_DATA produto;

    printf("\n--> CADASTRO DE PRODUTO: \n");
    printf("Insira o código do produto: ");
    scanf("%d", &produto.codigo);
    printf("Insira o nome do produto: ");
    scanf(" %[^\n]", produto.nome);
    printf("Insira a marca do produto: ");
    scanf(" %[^\n]", produto.marca);
    printf("Insira a categoria do produto: ");
    scanf(" %[^\n]", produto.categoria);
    printf("Insira a quantidade em estoque do produto: ");
    scanf("%d", &produto.estoque);
    printf("Insira o preço do produto: ");
    scanf("%f", &produto.preco);

    return produto;
}

// Função para imprimir os dados de um produto
void imprimir_produto(PRODUTO_DATA produto) {
    printf("\nDados do Produto:\n");
    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Marca: %s\n", produto.marca);
    printf("Categoria: %s\n", produto.categoria);
    printf("Estoque: %d\n", produto.estoque);
    printf("Preco: R$ %.2f\n", produto.preco);
}

void cadastrar_produto_sem_nos_livres(){

}

void cadastrar_produto(ARQUIVOS files){
    PRODUTO_DATA produto = ler_produto();
    imprimir_produto(produto);

    if(!tem_pos_livre_file_indices(files.file_indices)){
        // Realizar a inserção sem nós livres
        printf("A insercao sera realizada considerando que nao ha nos livres\n");
        cadastrar_produto_sem_nos_livres(files);
    }else{
        // Realizar a inserção verificando se o novo produto pode ser inserido em uma das posições livres
        printf("A insercao sera realizada considerando que ha nos livres\n");
    }

}
