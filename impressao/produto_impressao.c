//
// Created by andre on 08/04/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "produto_impressao.h"
#include "../insercao/produto_insercao.h"

// Function to print the contents of an ARVOREB tree
void imprimir_arvore(FILE * file_indices, int pos) {
    if (pos == -1) {
        return;
    }

    ARVOREB * no = ler_no(file_indices, pos);

    printf("Chaves: ");
    for (int i = 0; i < no->num_chaves; i++) {
        printf("%d ", no->chave[i]);
    }
    printf("\n");

    printf("Pt. Dados: ");
    for (int i = 0; i < no->num_chaves; i++) {
        printf("%d ", no->pt_dados[i]);
    }

    printf("\n");

    printf("Filhos: ");
    for (int i = 0; i <= no->num_chaves; i++) {
        printf("%d ", no->filho[i]);
    }
    printf("\n");

    for (int i = 0; i <= no->num_chaves; i++) {
        imprimir_arvore(file_indices, no->filho[i]);
    }

    free(no);
}