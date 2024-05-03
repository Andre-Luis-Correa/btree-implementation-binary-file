#ifndef FILE_H
#define FILE_H

#include "produto.h"
#include <stdio.h>
#include "file.h"

// Definição da estrutura ARQUIVOS
typedef struct {
    FILE * file_indices;        // Ponteiro para o arquivo de cursos
    FILE * file_dados;   // Ponteiro para o arquivo de disciplinas
} ARQUIVOS;

//Verificar se os arquivos binários já existem ou não
//Pré-condição: nenhuma
//Pós-condição: se aqrquivos existirem, então são abertos para leitura e escrita. Caso contrário, são criados e inicializados com uma lista vazia
void verificar_arquivos(ARQUIVOS * files);

//Fecha os aqrquivos
//Pré-condição: nenhuma
//Pós-condição: arquivos fechados
void fechar_arquivos(ARQUIVOS * files);

// Função para ler um nó do arquivo de índices da árvore B de produtos
// Pré-condições: O arquivo de índices deve existir e estar formatado corretamente
// Pós-condições: Retorna um ponteiro para o nó lido do arquivo de índices
ARVOREB * ler_no (FILE * file_indices, int pos);

// Função para escrever um nó no arquivo de índices
// Pré-condições: O arquivo de índices deve existir e estar formatado corretamente
// Pós-condições: O nó é escrito no arquivo de índices na posição especificada
void escreve_no (FILE * file_indices, ARVOREB * no, int pos);

// Função para ler um registro de dados de um produto no arquivo de dados
// Pré-condições: O arquivo de dados deve existir e estar formatado corretamente
// Pós-condições: Retorna um ponteiro para o registro lido do arquivo de dados
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos);

// Função para escrever um registro no arquivo de dados
// Pré-condições: O arquivo de dados deve existir e estar formatado corretamente
// Pós-condições: O registro é escrito no arquivo de dados na posição especificada
void escreve_registro (FILE * file_dados, DADOS_REGISTRO * registro, int pos);

#endif //FILE_H
