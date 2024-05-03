#ifndef LOTE_H
#define LOTE_H

#include "produto.h"
#include "arvore_utils.h"
#include "produto_insercao.h"
#include "produto_atualizacao.h"
#include "produto_remocao.h"

// Insere um lote de produtos no sistema
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: Os produtos do lote são inseridos no sistema, caso não existam ainda
void inserir_lote(ARQUIVOS files, PRODUTO_DATA produto);

// Atualiza o preço de um lote de produtos no sistema
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: O preço dos produtos do lote são atualizados no sistema
void atualizar_preco_lote(ARQUIVOS files, int codigo, float preco);

// Atualiza o estoque de um lote de produtos no sistema
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: O estoque dos produtos do lote são atualizados no sistema
void atualizar_estoque_lote(ARQUIVOS files, int codigo, int novo_estoque);

// Remove um lote de produtos do sistema
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: Os produtos do lote são removidos do sistema, caso existam
void remover_lote(ARQUIVOS files, int codigo);

// Processa uma linha do arquivo contendo informações sobre um lote de produtos
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: As operações correspondentes ao tipo de linha são realizadas no sistema
void processar_linha(ARQUIVOS files, char *linha);

// Lê um arquivo contendo lotes de produtos e processa suas linhas
// Pré-condições: Os arquivos de índices e de dados devem existir e estar formatados corretamente
// Pós-condições: As operações correspondentes às linhas do arquivo são realizadas no sistema
void ler_arquivo(ARQUIVOS files, char *nome_arquivo);

#endif //LOTE_H
