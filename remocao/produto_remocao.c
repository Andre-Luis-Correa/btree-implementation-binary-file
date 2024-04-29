#include <stdio.h>
#include <stdlib.h>
#include "produto_remocao.h"
#include "../utils/arvore_utils.h"

#define MIN (ORDEM/2 + ORDEM%2 - 1)

void remover_produto(ARQUIVOS files) {
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    int codigo, pos_codigo, pos_raiz, pos_esq, pos_dir;

    printf ("Insira o codigo a ser removido: ");
    scanf ("%d", &codigo);

    pos_codigo = buscar_no(files.file_indices, codigo);

    if(cab_indices->pos_raiz == -1){
        printf("A arvore encontra-se vazia!\n");
        free(cab_indices);
        return;
    } else if (pos_codigo == -1) {
        printf("Produto nao encontrado na arvore!\n");
        free(cab_indices);
        return;
    }

    printf("---> Iniciando a remocao da chave %d!\n", codigo);
    ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);
//    remover(files, raiz, codigo);

    free(raiz);
    free(cab_indices);
}

////retorna o irmao esquerdo ou NULL se não tem irmao esquerdo.
////pre-condição: arvore do filho que quer achar seu irmão esq, filho deve ter pai != NULL.
////pos-condição: no do irmão esquerdo
//ARVOREB * encontrar_irmao_esq(FILE * file_indices, ARVOREB * filho) {
//    int pos_pai, pos_filho;
//
//    pos_pai = buscar_pai(file_indices, filho->chave[0]);
//    pos_filho = buscar_no(file_indices, filho->chave[0]);
//
//    ARVOREB * pai = ler_no(file_indices, pos_pai);
//
//    if (!vazia(pai))
//    {
//        if (pos_filho == pai->filho[0])
//        {
//            free(pai);
//            return NULL;
//        }
//        int i = 0;
//        for (i = 0; i <= pai->numChaves; i++)
//        {
//            if (pai->filho[i] == filho->posicao)
//            {
//                arvoreB* irmao = le_no(file_indices, pai->filho[i - 1]);
//                free(pai);
//                return irmao;
//
//            }
//        }
//    }
//    return NULL;
//}
////pre-condiçao: arvore do filho que quer achar seu irmao direito, filho deve ter pai != NULL
////pos condição: nó com irmao direito
//ARVOREB * encontrar_irmao_dir(FILE* file_indices, ARVOREB * filho)
//{
//    arvoreB * pai = le_no(file_indices, filho->pai);
//
//    if (!vazia(pai))
//    {
//        if (filho->posicao == pai->filho[pai->numChaves])
//        {
//            free(pai);
//            return NULL;
//        }
//        int i = 0;
//        for (i = 0; i <= pai->numChaves; i++)
//        {
//            if (pai->filho[i] == filho->posicao)
//            {
//                arvoreB* irmao = le_no(file_indices, pai->filho[i + 1]);
//                free(pai);
//                return irmao;
//
//            }
//        }
//    }
//    return NULL;
//}
//
////verfica se um no pode sofrer emprestimo dos seus irmaos
////pre-condiçao: nó nao raiz
////pos-condiçao: retorna 1 se puder, 0 se nao puder
//int is_emprestimo(FILE* file_indices, ARVOREB * r)
//{
//    ARVOREB * esq = encontrar_irmao_esq(file_indices, r, pos_r);
//    ARVOREB * dir = encontrar_irmao_dir(file_indices, r, pos_r);
//
//    if (podeEmprestar(esq) || podeEmprestar(dir))
//    {
//        free(esq);
//        free(dir);
//        return 1;
//    }
//    free(esq);
//    free(dir);
//    return 0;
//
//}
//
////faz redistribuição se possível, ou faz concatenação para ajustar o no com underflow
////pré-condição: no que ficou com underflow
////pos-condição: balanceia o nó
//void balancear(FILE * file_indices, ARVOREB * r) {
//    if (is_emprestimo(file_indices, r)) {//se pode emprestar, faz a redistribuição
//        redistribuir(file_indices, r);
//    } else {                               //nao da pra emprestar, faz concatenação
//        concatenar(file_indices, r);
//    }
//}
//
////remove um produto
////pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
////pos-condição retorna a nova raiz;
//ARVOREB * remover (ARQUIVOS files, ARVOREB * r, int codigo) {
//    if (!vazia(r)) {
//        int i = 0;
//        for (i = 0; i < r->num_chaves; i++) { //varre o vetor em busca da chave se achar dá break
//            if (r->chave[i] == codigo) {
//                break;
//            } else if (r->chave[i] > codigo) { //compara o valor da arvore r atual com a chave a ser encontrada, se for maior busca no filho
//
//                ARVOREB * filho_i = ler_no(files.file_indices, r->filho[i]);
//
//                filho_i = remover(files, filho_i, codigo);
//
//                if (underflow(filho_i)) {
//                    balancear(files.file_indices, filho_i);
//                }
//                if (filho_i != NULL)
//                {
//                    r->filho[i] = filho_i->posicao;
//                    free(filho_i);
//                }
//                else
//                {
//                    r->filho[i] = -1;
//                }
//
//                int pos = r->posicao;
//                free(r);//libera o nó anterior
//                r = le_no(arqArv, pos);//atualiza o nó que foi mudado pelo balancear.
//                //escreve_no(arqArv, r, r->posicao);
//                //return r;
//            }
//        }
//        if (i >= r->numChaves)
//        { // nao encntrou a chave neste nó,todos os numero aqui sao menores que a chave, por isso procura no filho mais a direita
//            arvoreB* filho_i = le_no(arqArv, r->filho[i]);
//            filho_i = remover(arqProd, arqArv, filho_i, codigo);
//            if (filho_i != NULL)
//            {
//                r->filho[i] = filho_i->posicao;
//            }
//            else
//            {
//                r->filho[i] = -1;
//            }
//            if (underflow(filho_i))
//            {
//                balancear(arqArv, filho_i);
//            }
//        }
//        else
//        { //i é menor que núermo de chaves: achou algo neste nó,quando encontra a chave, sempre libera posições do arquivo de produto aqui
//            if (eh_folha(r))
//            {
//                addPosLivreProd(arqProd, r->ptDados[i]);
//                while (i + 1 < r->numChaves)
//                {
//                    r->chave[i] = r->chave[i + 1];
//                    r->ptDados[i] = r->ptDados[i + 1];
//                    i++;
//                }
//                r->numChaves--;//diminui uma chave;
//                escreve_no(arqArv, r, r->posicao);
//
//            }
//            else if (!eh_folha(r))
//            { //é no interno, não é folha
//                addPosLivreProd(arqProd, r->ptDados[i]);
//
//                arvoreB* filho_i = le_no(arqArv, r->filho[i]);
//                int pt = -1;
//                r->chave[i] = maximoRemove(arqArv, filho_i,&pt);
//                r->ptDados[i] = pt;
//                escreve_no(arqArv, r, r->posicao);
//                filho_i = remover(arqProd,arqArv,filho_i, r->chave[i]);
//                if (filho_i != NULL)
//                {
//                    r->filho[i] = filho_i->posicao;
//                }
//                else
//                {
//                    r->filho[i] = -1;
//                }
//                if (underflow(filho_i))
//                {
//                    balancear(arqArv,filho_i);
//                }
//
//            }
//
//        }
//        //testa se a raiz ficou vazia.
//        int pos = r->posicao;
//        free(r);
//        r = le_no(arqArv, pos);
//        if (r != NULL)
//        {
//
//            if (eh_raiz(r) && r->numChaves <= 0)
//            {
//                arvoreB* aux = le_no(arqArv, r->filho[0]);
//
//                if (aux != NULL)
//                {
//                    aux->pai = -1;
//                    mudarRaiz(arqArv, aux->posicao);
//                    escreve_no(arqArv, aux, aux->posicao);
//                }
//                else
//                {
//                    mudarRaiz(arqArv, -1);
//                }
//                addPosLivreArv(arqArv, r->posicao);
//                free(r);
//                r = NULL;
//                return aux;
//            }
//        }
//
//        if (r != NULL)
//        {
//
//            escreve_no(arqArv, r, r->posicao);
//        }
//        return r;
//
//    }
//
//    return NULL;
//}