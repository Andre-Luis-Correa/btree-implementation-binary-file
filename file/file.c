//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include "file.h"
#include "../cabecalho/cabecalho_dados.h"
#include "../cabecalho/cabecalho_indices.h"

//Verificar se os arquivos binários já existem ou não
//Pré-condição: nenhuma
//Pós-condição: se aqrquivos existirem, então são abertos para leitura e escrita. Caso contrário, são criados e inicializados com uma lista vazia
void verificar_arquivos(ARQUIVOS * files){
    if((files->file_indices = fopen("file_indices.bin", "r+b")) == NULL){
        printf("CRIANDO ARQUIVO DE INDICES...\n");
        files->file_indices = fopen("file_indices.bin", "w+b");
        cria_arvore_vazia_indices(files->file_indices);
    }
    if((files->file_dados = fopen("file_dados.bin", "r+b")) == NULL){
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
    fclose(files->file_dados);
    printf("\nFECHANDO ARQUIVO DE INDICES...");
    printf("\nFECHANDO ARQUIVO DE DADOS...\n");
}

//Verifica se um arquivo está vazio ou não, isto é: se contem registros ou não
//Pré-condição: nenhuma
//Pós-condição: retorna 1 se há registros e 0 caso não
int is_vazio_file_indices(FILE * file){
    CABECALHO_INDICES * cab = le_cabecalho_indices(file);
    return (cab->pos_topo == 0);
}

//Verifica se um arquivo está vazio ou não, isto é: se contem registros ou não
//Pré-condição: nenhuma
//Pós-condição: retorna 1 se há registros e 0 caso não
int is_vazio_file_dados(FILE * file){
    CABECALHO_DADOS * cab = le_cabecalho_dados(file);
    return (cab->pos_topo == 0);
}

int tem_pos_livre_file_indices(FILE * file){
    CABECALHO_INDICES* cab = le_cabecalho_indices(file);
    return (cab->pos_livre == 0);
}

int tem_pos_livre_file_dados(FILE * file){
    CABECALHO_DADOS * cab = le_cabecalho_dados(file);
    return (cab->pos_livre == 0);
}
