#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "../cabecalho/cabecalho_indices.h"
#include "../cabecalho/cabecalho_dados.h"

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

//Verifica se um arquivo está vazio ou não, isto é: se contem registros ou não
//Pré-condição: nenhuma
//Pós-condição: retorna 1 se há registros e 0 caso não
int is_vazio(ARQUIVOS files, int getFileIndices){

    if( getFileIndices ){
        CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
        int pos_raiz = cab_indices->pos_raiz;
        free(cab_indices);
        return pos_raiz == -1;

    }

    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    int pos_topo = cab_dados->pos_topo;
    free(cab_dados);
    return pos_topo == 0;
}

int tem_pos_livre(ARQUIVOS files, int getFileIndices){
    int pos_livre;

    if( getFileIndices ){
        CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
        pos_livre = cab_indices->pos_livre;
        free(cab_indices);
        return pos_livre != -1;
    }

    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);
    pos_livre = cab_dados->pos_livre;
    free(cab_dados);

    return pos_livre != -1;
}

// Função para ler um nó do arquivo de índices da árvore B de produtos
ARVOREB * ler_no (FILE * file_indices, int pos){
    if( pos == -1) return NULL;

    ARVOREB * no = (ARVOREB*) malloc(sizeof (ARVOREB));
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fread (no, sizeof (ARVOREB), 1, file_indices);
    return no;
}

// Função para escrever um nó no arquivo de índices
void escreve_no (FILE * file_indices, ARVOREB * no, int pos){
    fseek (file_indices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fwrite (no, sizeof (ARVOREB), 1, file_indices);
}

// Função para ler um registro de dados de um produto no arquivo de dados
DADOS_REGISTRO * ler_registro(FILE * file_dados, int pos){
    if( pos == -1) return NULL;

    DADOS_REGISTRO * registro = (DADOS_REGISTRO*) malloc(sizeof (DADOS_REGISTRO));
    fseek (file_dados, sizeof (CABECALHO_DADOS) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fread (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
    return registro;
}

// Função para escrever um nó no arquivo de índices
void escreve_registro (FILE * file_dados, DADOS_REGISTRO * registro, int pos){
    fseek (file_dados, sizeof (CABECALHO_DADOS ) + pos * sizeof (DADOS_REGISTRO), SEEK_SET);
    fwrite (registro, sizeof (DADOS_REGISTRO), 1, file_dados);
}

