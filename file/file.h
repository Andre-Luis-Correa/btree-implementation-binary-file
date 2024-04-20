//
// Created by andre on 08/04/2024.
//

#ifndef FILE_H
#define FILE_H

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

int is_vazio(ARQUIVOS files, int getFileIndices);

int tem_pos_livre(ARQUIVOS files, int getFileIndices);


#endif //FILE_H
