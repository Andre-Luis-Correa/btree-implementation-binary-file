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

//retorna o irmao esquerdo ou NULL se não tem irmao esquerdo.
//pre-condição: arvore do filho que quer achar seu irmão esq, filho deve ter pai != NULL.
//pos-condição: no do irmão esquerdo
ARVOREB * encontrar_irmao_esq(FILE * file_indices, ARVOREB * filho) {
    int pos_pai, pos_filho;

    pos_pai = buscar_pai(file_indices, filho->chave[0]);
    pos_filho = buscar_no(file_indices, filho->chave[0]);

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    if (!vazia(pai)) {
        if (pos_filho == pai->filho[0]) {
            free(pai);
            return NULL;
        }

        int i = 0;
        for (i = 0; i <= pai->num_chaves; i++)
        {
            if (pai->filho[i] == pos_filho)
            {
                ARVOREB * irmao = ler_no(file_indices, pai->filho[i - 1]);
                free(pai);
                return irmao;

            }
        }
    }
    return NULL;
}
//pre-condiçao: arvore do filho que quer achar seu irmao direito, filho deve ter pai != NULL
//pos condição: nó com irmao direito
ARVOREB * encontrar_irmao_dir(FILE* file_indices, ARVOREB * filho) {
    int pos_pai, pos_filho;

    pos_pai = buscar_pai(file_indices, filho->chave[0]);
    pos_filho = buscar_no(file_indices, filho->chave[0]);

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    if (!vazia(pai)) {
        if (pos_filho == pai->filho[pai->num_chaves]) {
            free(pai);
            return NULL;
        }
        int i = 0;
        for (i = 0; i <= pai->num_chaves; i++) {
            if (pai->filho[i] == pos_filho) {
                ARVOREB * irmao = ler_no(file_indices, pai->filho[i + 1]);
                free(pai);
                return irmao;

            }
        }
    }
    return NULL;
}

int pode_emprestar(ARVOREB * r) {
    if (r != NULL) {
        return r->num_chaves > MIN;
    }

    return 0;
}


//verfica se um no pode sofrer emprestimo dos seus irmaos
//pre-condiçao: nó nao raiz
//pos-condiçao: retorna 1 se puder, 0 se nao puder
int is_emprestimo(FILE* file_indices, ARVOREB * r)
{
    ARVOREB * esq = encontrar_irmao_esq(file_indices, r);
    ARVOREB * dir = encontrar_irmao_dir(file_indices, r);

    if (pode_emprestar(esq) || pode_emprestar(dir)) {
        free(esq);
        free(dir);
        return 1;
    }

    free(esq);
    free(dir);
    return 0;

}

//redistribui a arvore r com base no irmao esq que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao esq
void redistribuir_pela_esq(FILE* file_indices, ARVOREB * r, ARVOREB * esq) {
    int i, pos_chave_separadora, pos_pai, pos_r, pos_esq;

    pos_r = buscar_no(file_indices, r->chave[0]);
    pos_esq = buscar_no(file_indices, esq->chave[0]);
    pos_pai = buscar_pai(file_indices, r->chave[0]);
    pos_chave_separadora = buscar_pos_chave_separadora(file_indices, esq, r);//posicao da chave que separa os irmaos.

    for (i = r->num_chaves; i >= 0; i--){
        r->chave[i] = r->chave[i - 1];
        r->pt_dados[i] = r->pt_dados[i - 1];
        r->filho[i + 1] = r->filho[i];
    }

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    r->chave[0] = pai->chave[pos_chave_separadora];
    r->pt_dados[0] = pai->pt_dados[pos_chave_separadora];

    pai->chave[pos_chave_separadora] = esq->chave[esq->num_chaves - 1];
    pai->pt_dados[pos_chave_separadora] = esq->pt_dados[esq->num_chaves - 1];
    escreve_no(file_indices, pai, pos_pai);
    free(pai);

    r->filho[0] = esq->filho[esq->num_chaves];
    ARVOREB * filho = ler_no(file_indices, r->filho[0]);
    if (filho != NULL) {
        escreve_no(file_indices, filho, r->filho[0]);
        free(filho);
    }

    r->num_chaves++;

    esq->filho[esq->num_chaves] = -1;
    esq->num_chaves--;

    //atualiza os nós no arquivo
    escreve_no(file_indices, r, pos_r);
    escreve_no(file_indices, esq, pos_esq);
}

//redistribui a arvore r com base no irmao dir que pôde fazer emprestimo
//pre-condição: faz parte de remover, nao pode ser chamada solta
//pos-condição: redistribui r emprestando do irmao dir
void redistribuir_pela_dir(FILE* file_indices, ARVOREB * r, ARVOREB * dir){
    int i, pos_chave_separadora, pos_pai, pos_r, pos_dir;

    pos_r = buscar_no(file_indices, r->chave[0]);
    pos_dir = buscar_no(file_indices, dir->chave[0]);
    pos_pai = buscar_pai(file_indices, r->chave[0]);
    pos_chave_separadora = buscar_pos_chave_separadora(file_indices, r, dir);//posicao da chave que separa os irmãos

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    r->chave[r->num_chaves] = pai->chave[pos_chave_separadora];
    r->pt_dados[r->num_chaves++] = pai->pt_dados[pos_chave_separadora];

    pai->chave[pos_chave_separadora] = dir->chave[0];
    pai->pt_dados[pos_chave_separadora] = dir->pt_dados[0];
    escreve_no(file_indices, pai, pos_pai);
    free(pai);

    r->filho[r->num_chaves] = dir->filho[0];

    ARVOREB * filho = ler_no(file_indices, r->filho[r->num_chaves]);//rever se realmente precisa disso!!
    if (filho != NULL) {
        escreve_no(file_indices, filho, r->filho[r->num_chaves]);
        free(filho);
    }

    for (i = 0; i < dir->num_chaves; i++) {
        dir->chave[i] = dir->chave[i + 1];
        dir->pt_dados[i] = dir->pt_dados[i + 1];
        dir->filho[i] = dir->filho[i + 1];
    }

    dir->filho[dir->num_chaves] = -1;
    dir->num_chaves--;

    //atualiza os nós no arquivo.
    escreve_no(file_indices, dir, pos_dir);
    escreve_no(file_indices, r, pos_r);
}


//redistribui a arvore R com underflow
//pre-condição: função chamada automaticamente por balancear, nao deve ser chamada solta
//pos-condição: redistribui a árvore
void redistribuir(FILE* file_indices, ARVOREB * r) {
    ARVOREB * esq = encontrar_irmao_esq(file_indices, r);//usa memoria dinamica, liberar
    ARVOREB * dir = encontrar_irmao_dir(file_indices, r);//usa memoria dinamica, liberar
    int i = 0;

    if (pode_emprestar(esq)) {
        redistribuir_pela_esq(file_indices, r, esq);
        free(esq);

    } else if (pode_emprestar(dir)) {
        redistribuir_pela_dir(file_indices, r, dir);
        free(dir);

    }
}

//adiciona uma posicao às livres
//pre-condição: posicao válida  a ser adicionada a lista de livres
//pos-condição: atualiza cabecalho com a inclusao da posição
void atualizar_pos_livres_indices(FILE* file_indices, int pos) {
    CABECALHO_INDICES * cab = le_cabecalho_indices(file_indices);
    ARVOREB * no = ler_no(file_indices, pos);//REVER, era ler produto

    no->filho[0] = cab->pos_livre;
    escreve_no(file_indices, no, pos);
    cab->pos_livre = pos;
    escreve_cabecalho_indices(file_indices, cab);
    free(no);
    free(cab);
}

//adiciona uma posicao às livres
//pre-condição: posicao válida
//pos-condição: atualiza cabecalho com a inclusao da posição
void atualizar_pos_livres_dados(FILE* file_dados, int pos) {
    CABECALHO_DADOS * cab = le_cabecalho_dados(file_dados);
    PRODUTO_DATA * p = ler_registro(file_dados, pos);

    if (p != NULL) {
        p->codigo = cab->pos_livre;
        escreve_registro(file_dados, p, pos);
        cab->pos_livre = pos;
        escreve_cabecalho_dados(file_dados, cab);
        free(p);
    }
    free(cab);
}

//concatena r com seu irmao esquerdo = esq
//pré-condiçao: função aux, nunca chmar manualmente, testar se o irmao esq é diferente de null antes
//pos-condição: concatenação com irmao esquerdo
void concatenar_pela_esq(FILE* file_indices, ARVOREB * r, ARVOREB * esq) {
    ARVOREB * aux = r;//guarda o endereco de r para dar free e liberar a posicao depois que fizer a concatenação
    int pos_chave_separadora, pos_pai, pos_esq, pos_aux;

    pos_esq = buscar_no(file_indices, esq->chave[0]);
    pos_aux = buscar_no(file_indices, aux->chave[0]);
    pos_chave_separadora = buscar_pos_chave_separadora(file_indices, esq, r);//posicao da chave separadora.
    pos_pai = buscar_pai(file_indices, r->chave[0]);

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    esq->chave[esq->num_chaves] = pai->chave[pos_chave_separadora];
    esq->pt_dados[esq->num_chaves] = pai->pt_dados[pos_chave_separadora];
    esq->filho[esq->num_chaves + 1] = r->filho[0];

    ARVOREB * filho = ler_no(file_indices, esq->filho[esq->num_chaves + 1]);
    if (filho != NULL) {
        escreve_no(file_indices, filho, esq->filho[esq->num_chaves + 1]);
        free(filho);
        filho = NULL;
    }

    esq->num_chaves++;

    for (int i = 0; i < r->num_chaves; i++)
    {
        esq->chave[esq->num_chaves] = r->chave[i];
        esq->pt_dados[esq->num_chaves++] = r->pt_dados[i];
        filho = ler_no(file_indices, r->filho[i + 1]);

        if (filho != NULL) {
            escreve_no(file_indices, filho, r->filho[i + 1]);
            free(filho);
            filho = NULL;
        }
        esq->filho[esq->num_chaves] = r->filho[i + 1];
    }
    for (int i = pos_chave_separadora; i < pai->num_chaves; i++) {
        pai->chave[i] = pai->chave[i + 1];
        pai->pt_dados[i] = pai->pt_dados[i + 1];
        pai->filho[i + 1] = pai->filho[i + 2];
    }

    pai->num_chaves--;

    //atualiza o pai.
    escreve_no(file_indices, pai, pos_pai);//atualiza o pai
    free(pai);

    //atualiza irmão esquerdo:
    escreve_no(file_indices, esq, pos_esq);

    //adiciona a posicao que estava em r para as livres.
    atualizar_pos_livres_indices(file_indices, pos_aux);
    //free(aux);
    // aux = NULL;
}

//concatena r com seu irmao direito = dir
//pré-condiçao: função aux, nunca chamar manualmente, testar se o irmao dir é diferente de null antes
//pos-condição: concatenação com irmao direito
void concatenar_pela_dir(FILE* file_indices, ARVOREB * r, ARVOREB * dir) {
    int pos_chave_separadora, pos_pai, pos_r, pos_dir;

    pos_r = buscar_no(file_indices, r->chave[0]);
    pos_dir = buscar_no(file_indices, dir->chave[0]);
    pos_pai = buscar_pai(file_indices, r->chave[0]);
    pos_chave_separadora = buscar_pos_chave_separadora(file_indices, r, dir);//posição da chave separadora.

    ARVOREB * pai = ler_no(file_indices, pos_pai);

    r->chave[r->num_chaves] = pai->chave[pos_chave_separadora];
    r->pt_dados[r->num_chaves] = pai->pt_dados[pos_chave_separadora];
    r->filho[r->num_chaves + 1] = dir->filho[0];

    ARVOREB * filho = ler_no(file_indices, r->filho[r->num_chaves + 1]);
    if (filho != NULL) {
        escreve_no(file_indices, filho, r->filho[r->num_chaves + 1]);
        free(filho);
        filho = NULL;
    }
    r->num_chaves++;


    for (int i = 0; i < dir->num_chaves; i++) {
        r->chave[r->num_chaves] = dir->chave[i];
        r->pt_dados[r->num_chaves++] = dir->pt_dados[i];
        r->filho[r->num_chaves] = dir->filho[i + 1];

        filho = ler_no(file_indices, r->filho[r->num_chaves]);
        if (filho != NULL) {
            escreve_no(file_indices, filho, r->filho[r->num_chaves]);
            free(filho);
            filho = NULL;
        }
    }

    for (int i = pos_chave_separadora; i < pai->num_chaves; i++) {
        pai->chave[i] = pai->chave[i + 1];
        pai->pt_dados[i] = pai->pt_dados[i + 1];
        pai->filho[i + 1] = pai->filho[i + 2];//2 e 3
    }
    pai->num_chaves--;

    //atualiza o pai.
    escreve_no(file_indices, pai, pos_pai);
    free(pai);

    //atualiza o r.
    escreve_no(file_indices, r, pos_r);

    //adiciona a posicao do irmao da direita qeu se juntou com r às livres.
    atualizar_pos_livres_indices(file_indices, pos_dir);
    //free(dir);
    //dir = NULL;
}

//faz a concatenação, prioritariamente com o irmao esquerdo, se não o possuir, com o direito
// pré-condição: nó com underflow e que tenha sido redirecionado pela função balancear para fazer concatenação
//nao chamar esssa função manualmente, so deve ser chamada pela balancear
//pos-condição: concatena o no com o irmao sequerdo se possuir, ou direito caso nao possua irmao esquerdo
void concatenar(FILE* file_indices, ARVOREB * r) {
    ARVOREB * esq = encontrar_irmao_esq(file_indices, r);
    ARVOREB * dir = encontrar_irmao_dir(file_indices, r);

    if (esq != NULL) {//tem irmão esquerdo, pode concatenar com ele
        concatenar_pela_esq(file_indices, r, esq);
        free(esq);//dúvida sobre o free.
    } else if (dir != NULL) {//tem irmao direito pode concatenar com ele
        concatenar_pela_dir(file_indices, r, dir);
        free(dir);//dúvida sobre o free.
    }

}

//faz redistribuição se possível, ou faz concatenação para ajustar o no com underflow
//pré-condição: no que ficou com underflow
//pos-condição: balanceia o nó
void balancear(FILE * file_indices, ARVOREB * r) {
    if (is_emprestimo(file_indices, r)) {//se pode emprestar, faz a redistribuição
        redistribuir(file_indices, r);
    } else {                               //nao da pra emprestar, faz concatenação
        concatenar(file_indices, r);
    }
}

//remove um produto
//pre-condição: arqprod e arqArv, arquivos para produto e chaves respectivamente, válidos, r = leitura da raiz do arquivo de chaves
//pos-condição retorna a nova raiz;
ARVOREB * remover (ARQUIVOS files, ARVOREB * r, int codigo) {
    if (!vazia(r)) {
        int i = 0;
        for (i = 0; i < r->num_chaves; i++) { //varre o vetor em busca da chave se achar dá break
            if (r->chave[i] == codigo) {
                break;
            } else if (r->chave[i] > codigo) { //compara o valor da arvore r atual com a chave a ser encontrada, se for maior busca no filho

                ARVOREB * filho_i = ler_no(files.file_indices, r->filho[i]);

                filho_i = remover(files, filho_i, codigo);

                if (underflow(filho_i)) {
                    balancear(files.file_indices, filho_i);
                }

                if (filho_i != NULL) {
                    r->filho[i] = r->filho[i];
                    free(filho_i);
                } else {
                    r->filho[i] = -1;
                }

                int pos_r = buscar_no(files.file_indices, r->chave[0]);
                int pos = pos_r;
                free(r);//libera o nó anterior
                r = ler_no(files.file_indices, pos);//atualiza o nó que foi mudado pelo balancear.
            }
        }
        if (i >= r->num_chaves) { // nao encntrou a chave neste nó,todos os numero aqui sao menores que a chave, por isso procura no filho mais a direita
            ARVOREB * filho_i = ler_no(files.file_indices, r->filho[i]);
            filho_i = remover(files, filho_i, codigo);

            if (filho_i != NULL) {
                r->filho[i] = r->filho[i];
            } else {
                r->filho[i] = -1;
            }

            if (underflow(filho_i)) {
                balancear(files.file_indices, filho_i);
            }
        }
        else { //i é menor que núermo de chaves: achou algo neste nó,quando encontra a chave, sempre libera posições do arquivo de produto aqui
            if (eh_folha(r)) {
                atualizar_pos_livres_dados(files.file_dados, r->pt_dados[i]);
                while (i + 1 < r->num_chaves)
                {
                    r->chave[i] = r->chave[i + 1];
                    r->pt_dados[i] = r->pt_dados[i + 1];
                    i++;
                }
                int pos_r = buscar_no(files.file_indices, r->chave[0]);
                r->num_chaves--;//diminui uma chave;
                escreve_no(files.file_indices, r, pos_r);

            } else if (!eh_folha(r)) { //é no interno, não é folha
                atualizar_pos_livres_dados(files.file_dados, r->pt_dados[i]);

                ARVOREB * filho_i = le_no(arqArv, r->filho[i]);
                int pt = -1;
                r->chave[i] = maximoRemove(arqArv, filho_i,&pt);
                r->ptDados[i] = pt;
                escreve_no(arqArv, r, r->posicao);
                filho_i = remover(arqProd,arqArv,filho_i, r->chave[i]);
                if (filho_i != NULL)
                {
                    r->filho[i] = filho_i->posicao;
                }
                else
                {
                    r->filho[i] = -1;
                }
                if (underflow(filho_i))
                {
                    balancear(arqArv,filho_i);
                }

            }

        }
        //testa se a raiz ficou vazia.
        int pos = r->posicao;
        free(r);
        r = le_no(arqArv, pos);
        if (r != NULL)
        {

            if (eh_raiz(r) && r->numChaves <= 0)
            {
                arvoreB* aux = le_no(arqArv, r->filho[0]);

                if (aux != NULL)
                {
                    aux->pai = -1;
                    mudarRaiz(arqArv, aux->posicao);
                    escreve_no(arqArv, aux, aux->posicao);
                }
                else
                {
                    mudarRaiz(arqArv, -1);
                }
                addPosLivreArv(arqArv, r->posicao);
                free(r);
                r = NULL;
                return aux;
            }
        }

        if (r != NULL)
        {

            escreve_no(arqArv, r, r->posicao);
        }
        return r;

    }

    return NULL;
}