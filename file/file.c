#include <stdio.h>
#include <stdlib.h>
#include "file.h"

//Verificar se os arquivos binários já existem ou não
//Pré-condição: nenhuma
//Pós-condição: se aqrquivos existirem, então são abertos para leitura e escrita. Caso contrário, são criados e inicializados com uma lista vazia
void verificar_arquivos(ARQUIVOS * files){

    if((files->fileIndices = fopen("file_indices.bin", "r+b") ) == NULL ){
        printf("CRIANDO ARQUIVO DE INDICES...\n");
        files->fileIndices = fopen("file_indices.bin", "w+b");
        criaArvoreVaziaIndices(files->fileIndices);
    }

    if((files->fileRegistros = fopen("file_dados.bin", "r+b") ) == NULL ){
        printf("CRIANDO ARQUIVO DE DADOS...\n");
        files->fileRegistros = fopen("file_dados.bin", "w+b");
        criarRegistroVazio(files->fileDados);
        printf("\n");
    }
}

//Fecha os aqrquivos
//Pré-condição: nenhuma
//Pós-condição: arquivos fechados
void fecharArquivos(ARQUIVOS * files){
    fclose(files->fileIndices);
    printf("\nFECHANDO ARQUIVO DE INDICES...");
    fclose(files->fileRegistros);
    printf("\nFECHANDO ARQUIVO DE DADOS...\n");
}

//Verifica se um arquivo está vazio ou não, isto é: se contem registros ou não
//Pré-condição: nenhuma
//Pós-condição: retorna 1 se há registros e 0 caso não
int isVazio(ARQUIVOS files, int getFileIndices){

    if( getFileIndices ){
        CABECALHO_INDICES * cabIndices = lerCabecalhoIndices(files.fileIndices);
        int posRaiz = cabIndices->posRaiz;
        free(cabIndices);
        return posRaiz == -1;

    }

    CABECALHO_DADOS * cabRegistros = lerCabecalhoRegistros(files.fileRegistros);
    int posTopo = cabRegistros->posTopo;
    free(cabRegistros);
    return posTopo == 0;
}

int temPosLivre(ARQUIVOS files, int getFileIndices){
    int posLivre;

    if( getFileIndices ){
        CABECALHO_INDICES * cabIndices = lerCabecalhoIndices(files.fileIndices);
        posLivre = cabIndices->posLivre;
        free(cabIndices);
        return posLivre != -1;
    }

    CABECALHO_DADOS * cab_dados = lerCabecalhoRegistros(files.fileRegistros);
    posLivre = cab_dados->posLivre;
    free(cab_dados);

    return posLivre != -1;
}

// Função para ler um nó do arquivo de índices da árvore B de produtos
ARVOREB * lerNo (FILE * fileIndices, int pos){
    ARVOREB * no = (ARVOREB*) malloc(sizeof (ARVOREB));
    fseek (fileIndices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fread (no, sizeof (ARVOREB), 1, fileIndices);
    return no;
}

// Função para escrever um nó no arquivo de índices
void escreveNo (FILE * fileIndices, ARVOREB * no, int pos){
    fseek (fileIndices, sizeof (CABECALHO_INDICES) + pos * sizeof (ARVOREB), SEEK_SET);
    fwrite (no, sizeof (ARVOREB), 1, fileIndices);
}

// Função para ler um registro de dados de um produto no arquivo de dados
PRODUTO_REGISTRO * lerRegistro(FILE * fileDados, int pos){
    PRODUTO_REGISTRO * registro = (PRODUTO_REGISTRO*) malloc(sizeof (PRODUTO_REGISTRO));
    fseek (fileDados, sizeof (CABECALHO_DADOS) + pos * sizeof (PRODUTO_REGISTRO), SEEK_SET);
    fread (registro, sizeof (PRODUTO_REGISTRO), 1, fileDados);
    return registro;
}

// Função para escrever um nó no arquivo de índices
void escreveRegistro (FILE * fileDados, PRODUTO_REGISTRO * registro, int pos){
    fseek (fileDados, sizeof (CABECALHO_DADOS ) + pos * sizeof (PRODUTO_REGISTRO), SEEK_SET);
    fwrite (registro, sizeof (PRODUTO_REGISTRO), 1, fileDados);
}

