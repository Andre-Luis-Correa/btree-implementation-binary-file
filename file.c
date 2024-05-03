#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "cabecalho_indices.h"
#include "cabecalho_dados.h"

//Verificar se os arquivos binários já existem ou não
//Pré-condição: nenhuma
//Pós-condição: se aqrquivos existirem, então são abertos para leitura e escrita. Caso contrário, são criados e inicializados com uma lista vazia
void verificar_arquivos(ARQUIVOS * files){

    if((files->file_indices = fopen("file_indices.bin", "r+b") ) == NULL ){
        printf("CRIANDO ARQUIVO DE INDICES...\n");
        files->file_indices = fopen("file_indices.bin", "w+b");
        cria_arvore_vazia_indices(files->file_indices);
    }

    if((files->file_dados = fopen("file_dados.bin", "r+b") ) == NULL ){
        printf("CRIANDO ARQUIVO DE DADOS...\n");
        files->file_dados = fopen("file_dados.bin", "w+b");
        cria_arvore_vazia_dados(files->file_dados);
        printf("\n");
    }
}

//Fecha os aqrquivos
//Pré-condição: nenhuma
//Pós-condição: arquivos fechados
void fechar_arquivos(ARQUIVOS * files){
    fclose(files->file_indices);
    printf("\nFECHANDO ARQUIVO DE INDICES...");
    fclose(files->file_dados);
    printf("\nFECHANDO ARQUIVO DE DADOS...\n");
}

// Função para ler um nó do arquivo de índices da árvore B de produtos
// Pré-condições: O arquivo de índices deve existir e estar formatado corretamente
// Pós-condições: Retorna um ponteiro para o nó lido do arquivo de índices
ARVOREB * ler_no (FILE * file_indices, int pos){
    if( pos == -1) return NULL;

    ARVOREB * no = (ARVOREB*) malloc(sizeof (ARVOREB));
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fread (no, sizeof (ARVOREB), 1, file_indices);
    return no;
}

// Função para escrever um nó no arquivo de índices
// Pré-condições: O arquivo de índices deve existir e estar formatado corretamente
// Pós-condições: O nó é escrito no arquivo de índices na posição especificada
void escreve_no (FILE * file_indices, ARVOREB * no, int pos){
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fwrite (no, sizeof (ARVOREB), 1, file_indices);
}

// Função para ler um registro de dados de um produto no arquivo de dados
// Pré-condições: O arquivo de dados deve existir e estar formatado corretamente
// Pós-condições: Retorna um ponteiro para o registro lido do arquivo de dados
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos){
    if( pos == -1) return NULL;

    DADOS_REGISTRO * registro = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO));
    fseek (file_dados, sizeof (CABECALHO_DADOS) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fread (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
    return registro;
}

// Função para escrever um registro no arquivo de dados
// Pré-condições: O arquivo de dados deve existir e estar formatado corretamente
// Pós-condições: O registro é escrito no arquivo de dados na posição especificada
void escreve_registro (FILE * file_dados, DADOS_REGISTRO * registro, int pos){
    fseek (file_dados, sizeof (CABECALHO_DADOS ) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fwrite (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
}

