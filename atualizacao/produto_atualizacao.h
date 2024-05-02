//
// Created by andre on 09/04/2024.
//

#ifndef PRODUTO_ATUALIZACAO_H
#define PRODUTO_ATUALIZACAO_H

#include "../produto/produto.h"
#include "../file/file.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../cabecalho/cabecalho_dados.h"

void atualizar_preco_produto(ARQUIVOS files, int codigo_produto, float novo_preco);
void atualizar_estoque_produto(ARQUIVOS files, int codigo_produto, int novo_estoque);

#endif //PRODUTO_ATUALIZACAO_H