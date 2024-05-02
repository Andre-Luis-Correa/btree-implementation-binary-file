//
// Created by andre on 08/04/2024.
//

#ifndef LOTE_H
#define LOTE_H

#include "../produto/produto.h"
#include "../utils/arvore_utils.h"
#include "../insercao/produto_insercao.h"
#include "../atualizacao/produto_atualizacao.h"
#include "../remocao/produto_remocao.h"

void inserir_lote(ARQUIVOS files, PRODUTO_DATA produto);
void atualizar_preco_lote(ARQUIVOS files, int codigo, float preco);
void atualizar_estoque_lote(ARQUIVOS files, int codigo, int novo_estoque);
void remover_lote(ARQUIVOS files, int codigo);
void processar_linha(ARQUIVOS files, char *linha);
void ler_arquivo(ARQUIVOS files, char *nome_arquivo);

#endif //LOTE_H
