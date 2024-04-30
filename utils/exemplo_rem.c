////
//// Created by andre on 29/04/2024.
////
//
//arvoreB* remover(FILE* arqProd, FILE* arqArv, arvoreB* r, int x)
//{
//    if (!vazia(r))
//    {
//        int i = 0;
//        for (i = 0; i < r->numChaves; i++)
//        { //varre o vetor em busca da chave se achar dá break
//            if (r->chave[i] == x)
//            {
//                break;
//            }
//            else if (r->chave[i] > x)
//            { //compara o valor da arvore r atual com a chave a ser encontrada, se for maior busca no filho
//                arvoreB* filho_i = le_no(arqArv, r->filho[i]);
//                filho_i = remover(arqProd, arqArv, filho_i, x);
//                if (underflow(filho_i))
//                {
//                    balancear(arqArv, filho_i);
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
//            filho_i = remover(arqProd, arqArv, filho_i, x);
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