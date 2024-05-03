#ifndef PRODUTO_ATUALIZACAO_H
#define PRODUTO_ATUALIZACAO_H

#include "produto.h"
#include "file.h"
#include "cabecalho_indices.h"
#include "cabecalho_dados.h"

// Função para atualizar o preço de um produto a partir do seu código
// Pré-condições: O arquivo de índices e o arquivo de dados devem existir e estar formatados corretamente
// Pós-condições: O preço do produto é atualizado no arquivo de dados
void atualizar_preco_produto(ARQUIVOS files, int codigo_produto, float novo_preco);

// Função para atualizar o estoque de um produto a partir do seu código
// Pré-condições: O arquivo de índices e o arquivo de dados devem existir e estar formatados corretamente
// Pós-condições: O estoque do produto é atualizado no arquivo de dados
void atualizar_estoque_produto(ARQUIVOS files, int codigo_produto, int novo_estoque);

#endif //PRODUTO_ATUALIZACAO_H