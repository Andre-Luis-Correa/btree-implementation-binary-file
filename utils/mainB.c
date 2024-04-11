#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3

typedef struct no {
    int numChaves;
    int chave[ORDEM];
    struct no* filho[ORDEM+1];
} arvoreB;

int vazia (arvoreB * x){
    return x == NULL;
}

int overflow (arvoreB * x){
    return x->numChaves == ORDEM;
}

arvoreB* split (arvoreB* x, int * m){
    arvoreB* y = (arvoreB*) malloc (sizeof(arvoreB));
    int q = x->numChaves/2;
    y->numChaves = x->numChaves - q - 1;
    x->numChaves = q;
    *m = x->chave[q];
    int i = 0;
    y->filho[0] = x->filho[q+1];
    for (i = 0 ; i < y->numChaves ; i++){
        y->chave[i] = x->chave[q+i+1];
        y->filho[i+1] = x->filho[q+i+2];
    }
    return y;
}

int buscaPos (arvoreB* r, int info, int * pos){
    for ((*pos) = 0 ; (*pos) < r->numChaves ; (*pos)++){
        if (info == r->chave[(*pos)]){
            return 1;
        }
        else if (info < r->chave[(*pos)]){
            break;
        }
    }
    return 0;
}

int eh_folha (arvoreB * r){
    return (r->filho[0] == NULL);
}


void imprime_no(arvoreB * r){
    printf("[");
  for(int i = 0; i < r->numChaves;i++)
    printf("%d ", r->chave[i]);
  printf("]");
}

void adicionaDireita (arvoreB* r, int pos, int k, arvoreB * p){
    int i;
    for (i = r->numChaves ; i > pos ; i--){
        r->chave [i] = r->chave[i-1];
        r->filho[i+1] = r->filho[i];
    }
    r->chave[pos] = k;
    r->filho[pos+1] = p;
    r->numChaves++;
}

void insere_aux (arvoreB * r, int info){
    int pos;
    if (!buscaPos (r, info, &pos)){
        if (eh_folha(r)){
            adicionaDireita(r, pos, info, NULL);
        }
        else{
            insere_aux(r->filho[pos], info);
            if (overflow(r->filho[pos])){
                int m;
                arvoreB* aux = split(r->filho[pos], &m);
                adicionaDireita(r, pos, m, aux);
            }
        }
    }
}

arvoreB * insere (arvoreB* r, int info){
    if (vazia(r)){
        r = malloc(sizeof(arvoreB));
        r->chave[0] = info;
        for (int i = 0 ; i < ORDEM + 1 ; i++){
            r->filho[i] = NULL;
        }
        r->numChaves = 1;
    }
    else {
        insere_aux (r, info);
        if (overflow(r)){
            int m;
            arvoreB* x = split(r, &m);
            arvoreB* novaRaiz = malloc (sizeof(arvoreB));
            novaRaiz->chave[0] = m;
            novaRaiz->filho[0] = r;
            novaRaiz->filho[1] = x;
            for (int i = (((int) ORDEM/2) +1) ; i < ORDEM ; i++){
                r->filho[i] = NULL;
            }
            novaRaiz->numChaves = 1;
            return novaRaiz;
        }
    }
    return r;
}

void imprimir_in_ordem (arvoreB * r){
    if (!vazia(r)){
        for (int i = 0 ; i < r->numChaves ; i++){
            imprimir_in_ordem(r->filho[i]);
            printf("%d ", r->chave[i]);
        }
        imprimir_in_ordem(r->filho[r->numChaves]);
    }
}

int minimo (arvoreB * x){
    if (eh_folha(x)){
        return x->chave[0];
    }
    else {
        return minimo (x->filho[0]);
    }
}

int maximo (arvoreB * x){
    if (eh_folha(x)){
        return x->chave[x->numChaves-1];
    }
    else{
        return maximo(x->filho[x->numChaves]);
    }
}

int conta_nos_minimo_chaves(arvoreB* r){
    int c = 0;
    if (vazia(r)) return 0;
    for (int i = 0 ; i < r->numChaves; i++){
        if (r->numChaves > (ORDEM/2)){
            c += 0 + conta_nos_minimo_chaves(r->filho[i]);
        }
        else{
            c += 1 + conta_nos_minimo_chaves(r->filho[i]);
        }
    }
    return c + conta_nos_minimo_chaves(r->filho[r->numChaves]);
}

/*#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Definição da estrutura de um elemento
typedef struct Elemento {
    int chave;              // A chave do elemento
    int dado;               // O dado que cada elemento contém
} Elemento;

// Definição da estrutura de um nó da árvore B
typedef struct NoB {
    int numChaves;          // Número de chaves do nó
    int folha;              // Indica se este é um nó folha (1 = verdadeiro, 0 = falso)
    int posNoDisco;         // Posição do nó no arquivo
    Elemento *chaves;       // Vetor que armazena as chaves do nó
    int *filhos;            // Vetor que armazena os filhos do nó
} NoB;

// Definição da estrutura da árvore B
typedef struct ArvoreB {
    int ordem;              // Ordem da árvore B
    NoB raiz;               // Raiz da árvore B
    int contagemNos;        // Número total de nós na árvore
} ArvoreB;

// Protótipos das funções

ArvoreB *criarArvoreB(int ordem);

int buscarNaArvoreB(NoB no, int ordem, Elemento chave, FILE *arquivo);

void inserirNaArvoreB(ArvoreB *arvore, Elemento chave, FILE *arquivo);

void deletarDaArvoreB(ArvoreB *arvore, Elemento chave, FILE *arquivo);

void imprimirArvoreB(ArvoreB *arvore, Fila *fila, FILE *arquivo);

void destruirArvoreB(ArvoreB *arvore, FILE *arquivo);

Elemento encontrarMaximo(NoB no, int ordem, FILE *arquivo);

Elemento encontrarMinimo(NoB no, int ordem, FILE *arquivo);

NoB lerDoDisco(int posicao, int ordem, FILE *arquivo);

#endif // BTREE_H*/

