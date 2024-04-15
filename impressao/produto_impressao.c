//
// Created by andre on 08/04/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "produto_impressao.h"
#include "../insercao/produto_insercao.h"
#include "../file/file.h"

void imprimir_lista_produtos(ARQUIVOS files, int pos_atual) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos_atual == -1) {
        free(cab_indices);
        return;
    }else{
        ARVOREB *no = ler_no(files.file_indices, pos_atual);

        for (int i = 0; i <= no->num_chaves; i++) {
            imprimir_lista_produtos(files, no->filho[i]);

            if (i != no->num_chaves) {
                DADOS_REGISTRO *registro = ler_registro(files.file_dados, no->pt_dados[i]);
                printf("Codigo: %d \n Nome: %s \n Marca: %s \n Preco: %f \n", registro->produto.codigo, registro->produto.nome, registro->produto.marca, registro->produto.preco);
                printf("\n");
                free(registro);
            }
        }

        free(no);
        free(cab_indices);
    }

}

void imprimir_informacoes_produto(ARQUIVOS files, int codigo){
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    int pos = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);

    if(pos != -1) {
        ARVOREB * r = ler_no(files.file_indices, pos);

        int i;
        for(i = 0; i < r->num_chaves; i++){
            if(r->chave[i] == codigo) break;
        }

        DADOS_REGISTRO *informacoes_produto = ler_registro(files.file_dados, r->pt_dados[i]);
        printf("Codigo: %d \n Nome: %s \n Marca: %s \n Preco: %f \n", informacoes_produto->produto.codigo, informacoes_produto->produto.nome, informacoes_produto->produto.marca, informacoes_produto->produto.preco);
        free(informacoes_produto);
    } else {
        printf("Elemento nao encontrado!\n");
    }

    free(cab_indices);
}

//-----------------------------------IMPRIMIR NÍVEIS-----------------------------------------//

//busca o nível de uma chave na arvore R.
//pre-condição: arquivo válido de arvoreB, count começa em zero na primeira chamada
//pos-condição: o nivel da chave.
int buscaNivel(FILE* arq, ARVOREB* r, int chave, int count)
{
    if ( r!= NULL)
    {
        for (int i = 0; i < r->num_chaves; i++){
            if (r->chave[i] == chave)
            {
                return count;
            }
        }

        for (int i = 0; i < r->num_chaves; i++)
        {
            if (chave < r->chave[i])
            {
                ARVOREB* filho_i = ler_no(arq, r->filho[i]);
                if (filho_i != NULL)
                {
                    int retorno = 1 + buscaNivel(arq, filho_i, chave, count);
                    free(filho_i);
                    return retorno;
                }

            }
        }

        ARVOREB* filho_i = ler_no(arq, r->filho[r->num_chaves]);
        if (filho_i != NULL)
        {
            int retorno = 1 + buscaNivel(arq, filho_i, chave, count);
            free(filho_i);
            return retorno;
        }

    }
    return 0;
}
ARVOREB * busca(FILE* arq, ARVOREB* r, int info, int * pos)
{
    if (r == NULL)
        return NULL;
    int i = 0;
    while (i < r->num_chaves && r->chave[i] < info) i++;
    if ((i + 1) > r->num_chaves|| r->chave[i] > info)
    {
        ARVOREB* aux = ler_no(arq, r->filho[i]);
        ARVOREB* b = busca(arq, aux, info, pos);
        if (b != aux)
        {
            free(aux);
        }
        return b;
    }
    *pos = i;
    return r;
}

//testa se uma fila é vazia.
//pre-condição: fila válida
//pos-condição: retorna se a fila é vazia
int vaziaFila(Fila* f){
    return (f->inicio == NULL);
}

//enfileira um elemento na fila
//pre-condição: fila válida.
//pos-condição: nenhuma.
void enqueue(Fila* f, int x)
{
    struct noLista* aux = (struct noLista*)malloc(sizeof(struct noLista));
    aux->info = x;
    aux->prox = NULL;
    if (vaziaFila(f))
    {
        f->inicio = aux;
    }
    else
    {
        f->fim->prox = aux;
    }
    f->fim = aux;
}

//coloca os filhos na fila.
//pre-condição: arquivo valido para arvoreB.
//pos-condição: coloca os filhos na fila.
void enfileiraFilhos(FILE* arq, ARVOREB* r, Fila* f)
{
    ARVOREB* aux = NULL;
    int p = 0;
    aux = busca(arq,r, f->inicio->info,&p);

    if (aux != NULL)
    {
        if (aux->filho[0] != -1)
        {
            int i;
            for (i = 0; i <= aux->num_chaves; i++)
            {
                ARVOREB* filho_i = ler_no(arq, aux->filho[i]);
                if (filho_i != NULL)
                {
                    enqueue(f, filho_i->chave[0]);
                }
                free(filho_i);
                filho_i = NULL;
            }

        }
    }
}
//desinfileira uma fila.
int* dequeue(Fila* f)
{
    if (!vaziaFila(f))
    {
        int* x = (int*)malloc(sizeof(int));

        struct noLista* aux = f->inicio;
        *x = f->inicio->info;

        if (f->inicio == f->fim)
        {
            f->fim = NULL;
        }
        f->inicio = f->inicio->prox;
        free(aux);
        return x;
    }
    else
    {
        return NULL;
    }
}
//cria fila vazia
//pre-condiçao: nenhuma
//pos-condição: fila vazia criada.
Fila* cria_fila_vazia()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//imprimr as chave da arvoreB por níveis.
//pré-condição: raiz lida e arquivo valido para arvoreB.
//pos-condição: impressao da arvore por níveis.
void imprimir_por_niveis(ARQUIVOS files, ARVOREB* r)
{
    Fila* f = cria_fila_vazia();
    int atual = 0, ant = 0;
    if (r != NULL)
    {
        enqueue(f, r->chave[0]);
        while (!vaziaFila(f))
        {
            ARVOREB* aux = NULL;
            enfileiraFilhos(files.file_indices,r, f);
            atual = buscaNivel(files.file_indices,r, f->inicio->info, 0);
            if (atual != ant)
            {
                printf("\n");
                ant = atual;
            }
            int p = 0;
            aux = busca(files.file_indices,r, f->inicio->info,&p);
            int j;
            printf("[");
            for (j = 0; j < aux->num_chaves; j++)
            {
                printf("%d ", aux->chave[j]);
            }
            printf("] ");
            dequeue(f);
        }
    }
}


void imprimir_arvore(ARQUIVOS files) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);
    int pos =  cab_indices->pos_raiz;
    if (pos == -1) {
        free(cab_indices);
        return;
    } else {
        ARVOREB *no = ler_no(files.file_indices, pos);
        printf("Imprimindo Arvore por niveis :\n\n");
        imprimir_por_niveis(files, no);
    }
}
void imprimir_no(ARVOREB *r) {
    printf("\n-----------------------------\n");
    printf("    O no analisado foi: \n");

    printf("Chaves: ");
    for(int i = 0; i < r->num_chaves; i++){
        printf("%d ", r->chave[i]);
    }
    printf("\n");
    printf("Pt. Dados: ");
    for(int i = 0; i < r->num_chaves; i++){
        printf("%d ", r->pt_dados[i]);
    }
    printf("\n");
    printf("Filhos: ");
    for(int i = 0; i <= r->num_chaves; i++){
        printf("%d ", r->filho[i]);
    }
    printf("\n-----------------------------\n");
}


void imprimir_info_nos_chaves(ARQUIVOS files, int pos){
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);

    if (pos == -1) {
        //printf("Arvore vazia!\n");
        free(cab_indices);
        return;
    }else{
        ARVOREB * no = ler_no(files.file_indices, pos);
        imprimir_no(no);

        for(int i = 0; i <= no->num_chaves; i++){
            imprimir_info_nos_chaves(files, no->filho[i]);
        }

        free(no);
        free(cab_indices);
    }
}
