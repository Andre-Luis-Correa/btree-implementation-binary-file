//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_remocao.h"
#include "../insercao/produto_insercao.h"

int vazia(ARVOREB * r){
    return r->num_chaves == 0;
}

int eh_raiz(ARVOREB * r){
    int is_raiz = 1;

    for(int i = 0; i < r->num_chaves; i++){
        if(r->filho[i] != -1){
            is_raiz = 0;
            return is_raiz;
        }
    }

    return is_raiz;
}

int underflow(ARVOREB * r){
    if (!vazia(r)){
        if (r->num_chaves < ORDEM/2 && !eh_raiz(r) )
            return 1;
        return 0;
    }
    return 0;
}

void remover_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    int codigo, ha_codigo;
    printf ("Insira o codigo a ser removido: ");
    scanf ("%d", &codigo);

    ha_codigo = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);

    if(cab_indices->pos_raiz == -1){
        printf("A arvore encontra-se vazia!\n");
        free(cab_indices);
        return;
    } else if (ha_codigo == -1) {
        printf("Produto nao encontrado na arvore!\n");
        free(cab_indices);
        return;
    }

    ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);
    ARVOREB * no_removido = remover(files, raiz, codigo);

    free(no_removido);
    free(raiz);
    free(cab_indices);
}

void realizar_balanceamento(FILE * files_indices, ARVOREB * r)
{
    if (isEmprestimo(arqArv,r)){//se pode emprestar, faz a redistribuição
        redistribuir(arqArv,r);
    } else {//nao da pra emprestar, faz concatenação
        concatenar(arqArv,r);
    }
}

ARVOREB * remove_produto_file(ARQUIVOS files, ARVOREB * r, int codigo) {

    if(!vazia(r)) {
        int i = 0;
        for (i = 0; i < r->num_chaves; i++) { //varre o vetor em busca da chave se achar dá break
            if (r->chave[i] == codigo) {
                break;
            } else if (r->chave[i] > codigo) { //compara o valor da arvore r atual com a chave a ser encontrada, se for maior busca no filho
                ARVOREB * filho_pos_i = ler_no(files.file_indices, r->filho[i]);
                filho_pos_i = remover(files, filho_pos_i, codigo);
                if (underflow(filho_pos_i)) {
                    realizar_balanceamento(files.file_indices, filho_pos_i);
                } // Etou AQUIII
                if (filho_i != NULL) {
                    r->filho[i] = filho_i->posicao;
                    free(filho_i);
                } else {
                    r->filho[i] = -1;
                }

                int pos = r->posicao;
                free(r);//libera o nó anterior
                r = le_no(arqArv, pos);//atualiza o nó que foi mudado pelo balancear.
                //escreve_no(arqArv, r, r->posicao);
                //return r;
            }
        }
        if (i >=
            r->numChaves) { // nao encntrou a chave neste nó,todos os numero aqui sao menores que a chave, por isso procura no filho mais a direita
            arvoreB *filho_i = le_no(arqArv, r->filho[i]);
            filho_i = remover(arqProd, arqArv, filho_i, x);
            if (filho_i != NULL) {
                r->filho[i] = filho_i->posicao;
            } else {
                r->filho[i] = -1;
            }
            if (underflow(filho_i)) {
                balancear(arqArv, filho_i);
            }
        } else { //i é menor que núermo de chaves: achou algo neste nó,quando encontra a chave, sempre libera posições do arquivo de produto aqui
            if (eh_folha(r)) {
                addPosLivreProd(arqProd, r->ptDados[i]);
                while (i + 1 < r->numChaves) {
                    r->chave[i] = r->chave[i + 1];
                    r->ptDados[i] = r->ptDados[i + 1];
                    i++;
                }
                r->numChaves--;//diminui uma chave;
                escreve_no(arqArv, r, r->posicao);

            } else if (!eh_folha(r)) { //é no interno, não é folha
                addPosLivreProd(arqProd, r->ptDados[i]);

                arvoreB *filho_i = le_no(arqArv, r->filho[i]);
                int pt = -1;
                r->chave[i] = maximoRemove(arqArv, filho_i, &pt);
                r->ptDados[i] = pt;
                escreve_no(arqArv, r, r->posicao);
                filho_i = remover(arqProd, arqArv, filho_i, r->chave[i]);
                if (filho_i != NULL) {
                    r->filho[i] = filho_i->posicao;
                } else {
                    r->filho[i] = -1;
                }
                if (underflow(filho_i)) {
                    balancear(arqArv, filho_i);
                }

            }

        }
        //testa se a raiz ficou vazia.
        int pos = r->posicao;
        free(r);
        r = le_no(arqArv, pos);
        if (r != NULL) {

            if (eh_raiz(r) && r->numChaves <= 0) {
                arvoreB *aux = le_no(arqArv, r->filho[0]);

                if (aux != NULL) {
                    aux->pai = -1;
                    mudarRaiz(arqArv, aux->posicao);
                    escreve_no(arqArv, aux, aux->posicao);
                } else {
                    mudarRaiz(arqArv, -1);
                }
                addPosLivreArv(arqArv, r->posicao);
                free(r);
                r = NULL;
                return aux;
            }
        }

        if (r != NULL) {

            escreve_no(arqArv, r, r->posicao);
        }
        return r;
    }

    return NULL;
}
