//
// Created by andre on 08/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "produto_remocao.h"

#define MIN (ORDEM/2 + ORDEM%2 - 1)

void remover_produto(ARQUIVOS files){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    int codigo, pos_codigo, pos_raiz, pos_esq, pos_dir;

    printf ("Insira o codigo a ser removido: ");
    scanf ("%d", &codigo);

    pos_codigo = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);

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
    remover(files, codigo, cab_indices->pos_raiz, pos_codigo);

    free(raiz);
    free(cab_indices);
}

int mais_chaves_que_min(ARVOREB * r){
    return r->num_chaves > MIN;
}

int busca_pos_chave(ARVOREB * r, int codigo){
    int pos_codigo;

    // Encontra a pos dentro do nó
    for(pos_codigo = 0; pos_codigo < r->num_chaves; pos_codigo++){
        if( r->chave[pos_codigo] == codigo)
            return pos_codigo;
    }

    return -1;
}

void atualiza_lista_dados_livres(ARQUIVOS files, CABECALHO_DADOS * cab_dados, int pos_registro){
    printf("\n---> Atualizando dados livres!\n");
    DADOS_REGISTRO * dados_atual = ler_registro(files.file_dados, cab_dados->pos_livre);

    int prox = cab_dados->pos_livre;

    while(dados_atual->prox_livre != -1){
        prox = dados_atual->prox_livre;
        if(prox == -1) break;
        free(dados_atual);
        dados_atual = ler_registro(files.file_dados, prox);
    }
    printf("\n---> Ainda atualizando dados livres!\n");
    dados_atual->prox_livre = pos_registro;
    escreve_registro(files.file_dados, dados_atual, prox);
    free(dados_atual);
}

void atualiza_no_remocao_folha(ARQUIVOS files, ARVOREB * folha, int pos_remocao, int pos_codigo){
    CABECALHO_DADOS * cab_dados = le_cabecalho_dados(files.file_dados);

    // A posição dos dados no arq de dados deve ser atualizado
    // folha->pt_dados[pos_codigo] => posição dos dados no file de dados
    int pos_registro = folha->pt_dados[pos_codigo];

    if(cab_dados->pos_livre == -1){
        cab_dados->pos_livre = pos_registro;
        // Atualiza o cab_dados com a posição livre
        escreve_cabecalho_dados(files.file_dados, cab_dados);

    }else {
        printf("\n---> Atualizando lista de dados livres!\n");
        atualiza_lista_dados_livres(files, cab_dados, pos_registro);
    }

    printf("\n ---> CASO 1 - ANTES ATT - REMOCAO: \n");
    imprimir_no(folha);

    // Agora realizar a atualização do nó folha
    int i;
    for(i = pos_codigo; i < folha->num_chaves-1; i++){
        folha->chave[i] = folha->chave[i+1];
        folha->pt_dados[i] = folha->pt_dados[i+1];
        folha->filho[i] = folha->filho[i+1];
    }

    // Atualiza o último fiilho
    folha->filho[i] = folha->filho[folha->num_chaves];
    folha->num_chaves--;

    printf("\n ---> CASO 1 - DEPOIS ATT - REMOCAO: \n");
    imprimir_no(folha);

    escreve_no(files.file_indices, folha, pos_remocao);
    free(cab_dados);
}

// 1° CASO: a remoção é feita em um nó folha com número de chaves maior que o mínimo (ORDEM/2)
void remover_caso1(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao){
    int pos_codigo, i;

    // Encontra a pos dentro do nó
    pos_codigo = busca_pos_chave(no_a_remover, codigo);
    atualiza_no_remocao_folha(files, no_a_remover, pos_remocao, pos_codigo);
}

int buscar_chave_sucessora_folha(ARQUIVOS files, ARVOREB * no_a_remover, int pos_codigo, int * pos_no_sucessor){
    int pos_chave_sucessora = no_a_remover->filho[pos_codigo + 1];
    int chave_sucessora;

    ARVOREB * no_sucessor = ler_no(files.file_indices, pos_chave_sucessora);

    if(eh_folha(no_sucessor)){
        *pos_no_sucessor = pos_chave_sucessora;
        chave_sucessora = no_sucessor->chave[0];
        printf("\n ----> Essa é a chave sucessora: %d\n", chave_sucessora);
        free(no_sucessor);
        return chave_sucessora;
    }

    return buscar_chave_sucessora_folha(files, no_sucessor, -1, pos_no_sucessor);
}

int remover_caso2(ARQUIVOS files, ARVOREB * no_a_remover, int codigo, int pos_remocao){
    // Primeiramente, busca a posição da chave (dentro do nó) a ser removida no nó
    int pos_codigo = busca_pos_chave(no_a_remover, codigo);
    int pos_no_sucessor;

    // Busca a chave sucessora para inseri-lá na pos_codigo encontrada
    // Também retorna a posição no arq de indices do nó sucessor
    int chave_sucessora = buscar_chave_sucessora_folha(files, no_a_remover, pos_codigo, &pos_no_sucessor);

    // Preciso atualizar a folha que continha a chave sucessora
    ARVOREB  * no_sucessor = ler_no(files.file_indices, pos_no_sucessor);

    int pt_dados_remocao = no_sucessor->pt_dados[0];

    atualiza_no_remocao_folha(files, no_sucessor, pos_no_sucessor, 0);

    // Realiza a substituição da chave removida pela chave sucessora
    no_a_remover->chave[pos_codigo] = chave_sucessora;
    no_a_remover->pt_dados[pos_codigo] = pt_dados_remocao;
    escreve_no(files.file_indices, no_a_remover, pos_remocao);

    return pos_no_sucessor;
}

int buscar_pai(ARQUIVOS files, int pos_raiz, int codigo, int *pos_filho_remocao) {
    ARVOREB *r = ler_no(files.file_indices, pos_raiz);

    // Verifica se é uma folha
    if (eh_folha(r)) {
        *pos_filho_remocao = -1; // Marca o filho de remoção como inexistente
        return -1; // Retorna -1 indicando que não foi encontrado
    }

    int i;
    for (i = 0; i < r->num_chaves; i++) {
        // Se o código for menor que a chave atual, desce para o filho à esquerda
        if (codigo < r->chave[i]) {
            ARVOREB *filho = ler_no(files.file_indices, r->filho[i]);
            int pos_codigo = busca_pos_chave(filho, codigo);
            free(filho);
            // Se a chave for encontrada no filho, retorna o nó atual como pai
            if (pos_codigo != -1) {
                *pos_filho_remocao = i;
                return pos_raiz;
            }
            // Se não, continua a busca descendente
            return buscar_pai(files, r->filho[i], codigo, pos_filho_remocao);
        }
    }

    // Se o código for maior que todas as chaves, desce para o último filho
    ARVOREB * filho = ler_no(files.file_indices, r->filho[i]);
    int pos_codigo = busca_pos_chave(filho, codigo);
    free(filho);

    // Se a chave for encontrada no último filho, retorna o nó atual como pai
    if (pos_codigo != -1) {
        *pos_filho_remocao = i;
        return pos_raiz;
    }

    // Se não, continua a busca descendente
    return buscar_pai(files, r->filho[i], codigo, pos_filho_remocao);
}

int pode_redistribuir(ARQUIVOS files, int pos_pai, int pos_filho_remocao, int * pegar_esq, int * pegar_dir) {
    // Buscar o pai
    ARVOREB *pai = ler_no(files.file_indices, pos_pai);
    ARVOREB *esq = (ARVOREB *) malloc(sizeof(ARVOREB));
    ARVOREB *dir = (ARVOREB *) malloc(sizeof(ARVOREB));
    imprimir_no(pai);
    printf("\n---> pos filho remocao: %d\n", pos_filho_remocao);
    // Depois obter os filhos a esquerda e direita
    if (pos_filho_remocao == 0) {
        dir = ler_no(files.file_indices, pai->filho[1]);
        if (dir->num_chaves > MIN) {
            printf("\n----> Pode emprestar a dir e nao esq!\n");
            imprimir_no(esq);
            imprimir_no(dir);
            *pegar_esq = -1;
            *pegar_dir = pai->filho[1];
            return 1;
        }
    } else if ( pos_filho_remocao == pai->num_chaves ){
        esq = ler_no(files.file_indices, pai->filho[pai->num_chaves - 1]);
        if (esq->num_chaves > MIN) {
            printf("\n----> Pode emprestar a esq e nao dir!\n");
            imprimir_no(esq);
            imprimir_no(dir);
            *pegar_esq = pai->filho[pai->num_chaves - 1];
            *pegar_dir = -1;
            return 1;
        }
    } else {
        esq = ler_no(files.file_indices, pai->filho[pos_filho_remocao - 1]);
        dir = ler_no(files.file_indices, pai->filho[pos_filho_remocao + 1]);

        imprimir_no(esq);
        imprimir_no(dir);
        printf("\n-----> Esse é o numero de chaves da dir e o min: %d => %d\n", dir->num_chaves,  MIN);
        printf("\n-----> Esse é o numero de chaves da esq e o min: %d => %d\n", esq->num_chaves,  MIN);

        if (dir->num_chaves > MIN) {
            printf("\n----> Pode emprestar a dir e nao esq!\n");
            imprimir_no(esq);
            imprimir_no(dir);
            *pegar_esq = -1;
            *pegar_dir = pai->filho[pos_filho_remocao + 1];
            return 1;

        } else if (esq->num_chaves > MIN) {
            printf("\n----> Pode emprestar a esq e nao dir!\n");
            imprimir_no(esq);
            imprimir_no(dir);
            *pegar_esq = pai->filho[pos_filho_remocao - 1];
            *pegar_dir = -1;
            return 1;
        }
    }

    printf("\n----> Nao pode ocorrer emprestimo!\n");

    *pegar_esq = -1;
    *pegar_dir = -1;
    free(esq);
    free(dir);
    return 0;
}

void redistribuir_partir_da_direita(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_dir){
    ARVOREB * pai = ler_no(files.file_indices, pos_pai);
    ARVOREB * no_remocao = ler_no(files.file_indices, pos_remocao);
    ARVOREB * dir = ler_no(files.file_indices, pegar_dir);

    no_remocao->chave[no_remocao->num_chaves] = pai->chave[pos_filho_remocao];
    no_remocao->pt_dados[no_remocao->num_chaves] = pai->pt_dados[pos_filho_remocao];
    no_remocao->num_chaves++;
    no_remocao->filho[no_remocao->num_chaves] = dir->filho[0];

    pai->chave[pos_filho_remocao] = dir->chave[0];
    pai->pt_dados[pos_filho_remocao] = dir->pt_dados[0];


    int i;
    for(i = 0; i < dir->num_chaves - 1; i++){
        dir->chave[i] = dir->chave[i+1];
        dir->pt_dados[i] = dir->pt_dados[i+1];
        dir->filho[i] = dir->filho[i+1];
    }
    dir->filho[i] = dir->filho[dir->num_chaves];
    dir->num_chaves--;

    escreve_no(files.file_indices, pai, pos_pai);
    escreve_no(files.file_indices, no_remocao, pos_remocao);
    escreve_no(files.file_indices, dir, pegar_dir);
}

void redistribuir_partir_da_esquerda(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq){
    ARVOREB *pai = ler_no(files.file_indices, pos_pai);
    ARVOREB *no_remocao = ler_no(files.file_indices, pos_remocao);
    ARVOREB *esq = ler_no(files.file_indices, pegar_esq);

    // Movendo a chave e o ponteiro de dados do pai para o nó de remoção
    int i;
    for(i = no_remocao->num_chaves; i > 0; i--){
        no_remocao->chave[i] = no_remocao->chave[i - 1];
        no_remocao->pt_dados[i] = no_remocao->pt_dados[i - 1];
        no_remocao->filho[i + 1] = no_remocao->filho[i];
    }
    no_remocao->filho[1] = no_remocao->filho[0];
    no_remocao->chave[0] = pai->chave[pos_filho_remocao - 1];
    no_remocao->pt_dados[0] = pai->pt_dados[pos_filho_remocao - 1];
    no_remocao->num_chaves++;

    // Movendo a chave e o ponteiro de dados do nó esquerdo para o pai
    pai->chave[pos_filho_remocao - 1] = esq->chave[esq->num_chaves - 1];
    pai->pt_dados[pos_filho_remocao - 1] = esq->pt_dados[esq->num_chaves - 1];

    // Movendo o filho mais à direita do nó esquerdo para o nó de remoção
    no_remocao->filho[0] = esq->filho[esq->num_chaves];

    // Atualizando o nó esquerdo
    esq->num_chaves--;

    // Escrevendo as alterações de volta nos arquivos
    escreve_no(files.file_indices, pai, pos_pai);
    escreve_no(files.file_indices, no_remocao, pos_remocao);
    escreve_no(files.file_indices, esq, pegar_esq);
}

void redistribuir(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq, int pegar_dir){

    if(pegar_dir != -1){
        redistribuir_partir_da_direita(files, pos_pai, pos_remocao, pos_filho_remocao, pegar_dir);
    } else {
        redistribuir_partir_da_esquerda(files, pos_pai, pos_remocao, pos_filho_remocao, pegar_esq);
    }

}
void buscar_filhos_esq_dir(ARQUIVOS files, int pos_pai, int pos_filho_remocao, int * pegar_esq, int * pegar_dir){
    // Buscar o pai
    ARVOREB *pai = ler_no(files.file_indices, pos_pai);
    ARVOREB *esq = (ARVOREB *) malloc(sizeof(ARVOREB));
    ARVOREB *dir = (ARVOREB *) malloc(sizeof(ARVOREB));
    imprimir_no(pai);

    printf("\n -- pos raiz: %d\n", pos_pai);
    printf("\n---> pos filho remocao: %d\n", pos_filho_remocao);

    // Depois obter os filhos a esquerda e direita
    if (pos_filho_remocao == 0) {
        printf("\n--> entrou aqui:   if (pos_filho_remocao == 0) \n");
        *pegar_dir = pai->filho[1];
        *pegar_esq = -1;
        return;
    } else if ( pos_filho_remocao == pai->num_chaves ){
        printf("\n--> entrou aqui:   ( pos_filho_remocao == pai->num_chaves ) \n");
        *pegar_esq = pai->filho[pai->num_chaves-1];
        *pegar_dir = -1;
        return;
    }

    printf("\n-->NAOOAOAOAOOAOAOAOAOAOA aqui: \n");
    *pegar_esq = pai->filho[pos_filho_remocao-1];
    *pegar_dir = pai->filho[pos_filho_remocao+1];
}

void atualizar_pos_livres_indices(ARQUIVOS files, int pos_livre){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    if(cab_indices->pos_livre == -1){
        cab_indices->pos_livre = pos_livre;
        return;
    }

    ARVOREB * no_atual = ler_no(files.file_indices, cab_indices->pos_livre);
    int pos_atual = cab_indices->pos_livre;


    while(no_atual->prox_livre !=-1){
        pos_atual = no_atual->prox_livre;
        no_atual = ler_no(files.file_indices, no_atual->prox_livre);
    }

    no_atual->prox_livre = pos_livre;
    escreve_no(files.file_indices, no_atual, pos_atual);
    free(no_atual);
    free(cab_indices);
}

void concatenar_esquerda(ARQUIVOS files, ARVOREB * pai, ARVOREB * esq, ARVOREB * no_a_remover, int pos_filho_remocao){

    int i;

    esq->chave[esq->num_chaves] = pai->chave[pos_filho_remocao-1];
    esq->pt_dados[esq->num_chaves] = pai->pt_dados[pos_filho_remocao-1];
    esq->num_chaves++;

    // Trazer as infos do nó removido para o nó da esquerda
    for(i = 0; i < no_a_remover->num_chaves; i++){
        esq->chave[esq->num_chaves] = no_a_remover->chave[i];
        esq->pt_dados[esq->num_chaves] = no_a_remover->pt_dados[i];
        esq->filho[esq->num_chaves] = no_a_remover->filho[i];
        esq->num_chaves++;
    }

    esq->filho[esq->num_chaves] = no_a_remover->filho[i];

    // Atualizar a lista de livres, pois agora o nó removido é vazio (NULL = -1)
    atualizar_pos_livres_indices(files, pai->filho[pos_filho_remocao]);

    // Atualizar nó pai
    for(i = pos_filho_remocao-1; i < pai->num_chaves-1; i++){
        pai->chave[i] = pai->chave[i+1];
        pai->pt_dados[i] = pai->pt_dados[i+1];
        pai->filho[i+1] = pai->filho[i+2];
    }

    pai->num_chaves--;
}

void concatenar_direita(ARQUIVOS files, ARVOREB * pai, ARVOREB * dir, ARVOREB * no_a_remover, int pos_filho_remocao){
    int i;

    // Mover a chave do pai para o nó a ser removido na posição correta
    no_a_remover->chave[no_a_remover->num_chaves] = pai->chave[pos_filho_remocao];
    no_a_remover->pt_dados[no_a_remover->num_chaves] = pai->pt_dados[pos_filho_remocao];
    no_a_remover->num_chaves++;

    printf("\n-->NO A REMOVER APoS adiconair o pai!\n");
    imprimir_no(no_a_remover);

    // Trazer as informações do nó direito para o nó a ser removido
    for (i = 0; i < dir->num_chaves; i++) {
        no_a_remover->chave[no_a_remover->num_chaves] = dir->chave[i];
        no_a_remover->pt_dados[no_a_remover->num_chaves] = dir->pt_dados[i];
        no_a_remover->filho[no_a_remover->num_chaves] = dir->filho[i];
        no_a_remover->num_chaves++;
    }
    no_a_remover->filho[no_a_remover->num_chaves] = dir->filho[i]; // Último filho

    printf("\n-->NO A REMOVER APoS adiconair a dir!\n");
    imprimir_no(no_a_remover);

    // Atualizar a lista de livres, pois o nó direito agora está vazio
    atualizar_pos_livres_indices(files, pai->filho[pos_filho_remocao+1]);

    // Atualizar nó pai
    for (i = pos_filho_remocao; i < pai->num_chaves - 1; i++) {
        pai->chave[i] = pai->chave[i + 1];
        pai->pt_dados[i] = pai->pt_dados[i + 1];
        pai->filho[i + 1] = pai->filho[i + 2];
    }

    pai->num_chaves--;

    printf("\n-->NO PAI APOS CONCATENACAO!\n");
    imprimir_no(pai);
}

void concatenar(ARQUIVOS files, int pos_pai, int pos_remocao, int pos_filho_remocao, int pegar_esq, int pegar_dir){
    printf("\n---> INICIANDO A CONCATENAÇÂO\n");
    ARVOREB * pai = ler_no(files.file_indices, pos_pai);
    ARVOREB * no_a_remover = ler_no(files.file_indices, pos_remocao);
    ARVOREB *esq = (ARVOREB *) malloc(sizeof(ARVOREB));
    ARVOREB *dir = (ARVOREB *) malloc(sizeof(ARVOREB));
    imprimir_no(pai);
    imprimir_no(no_a_remover);

    if(pegar_dir == -1){
        printf("\n---> Não tem direita, então faz concatenação com a esquerda\n");
        esq = ler_no(files.file_indices, pegar_esq);
        concatenar_esquerda(files, pai, esq, no_a_remover, pos_filho_remocao);
        escreve_no(files.file_indices, pai, pos_pai);
        escreve_no(files.file_indices, esq, pegar_esq);
    } else {
        printf("\n---> Tem ou nao tem esq, então faz concatenação com a direita\n");
        dir = ler_no(files.file_indices, pegar_dir);
        printf("\n---> esse é o filho da dir!\n");
        imprimir_no(dir);
        printf("\n---> esse é o no pai!\n");
        imprimir_no(pai);
        printf("\n---> esse é o no a remover!\n");
        imprimir_no(no_a_remover);
        concatenar_direita(files, pai, dir, no_a_remover, pos_filho_remocao);
        escreve_no(files.file_indices, pai, pos_pai);
        escreve_no(files.file_indices, no_a_remover, pos_remocao);
    }

    free(pai);
    free(no_a_remover);
    free(esq);
    free(dir);
}

void verificar_redistribuicao_ou_concatenacao(ARQUIVOS files, int pos_raiz, ARVOREB * no_a_remover, int pos_pai, int pos_filho_remocao, int pos_remocao, int codigo) {
    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);
    // Busca o pai para poder veirificar os filhos irmão e verificar se podem emprestar
    printf("\n  ----> POS PAI: %d\n", pos_pai);

    if (pos_pai != -1) {
        // 1° Verifica-se se é possícel realizar a redistribuição
        int pegar_esq, pegar_dir;
        // A função pode_redistribuir() verifica se é possível realizar a redistribuição e indica a partir de qual lado
        int teste_pode_redistribuir = pode_redistribuir(files, pos_pai, pos_filho_remocao, &pegar_esq, &pegar_dir);
        printf("\n-----------Esse é o teste redistribuir: %d\n", teste_pode_redistribuir);

        if (teste_pode_redistribuir) {
            printf("\n---> Será fieito a redistribuição!\n");
            // Aqui será inserido a lógica da redistribuição
            // A função pode_redistribuir guarda a posição no arquivo dos filhos da esq e dir
            redistribuir(files, pos_pai, pos_remocao, pos_filho_remocao, pegar_esq, pegar_dir);
        } else {
            printf("\n---> Não será feito a redistribuição, mas sim, a concatenação");
            // Aqui será inserido a lógica da concatenação
            buscar_filhos_esq_dir(files, pos_pai, pos_filho_remocao, &pegar_esq, &pegar_dir);
            printf("\n--> FILHOS a esq e dir\n");
            ARVOREB * esq = ler_no(files.file_indices, pegar_esq);
            ARVOREB * dir  = ler_no(files.file_indices, pegar_dir);
            imprimir_no(esq);
            imprimir_no(dir);
            concatenar(files, pos_pai, pos_remocao, pos_filho_remocao, pegar_esq, pegar_dir);
        }
    }

    free(cab_indices);
}


void remover_caso4(ARQUIVOS files, int pos_raiz, int pos_pai){
    ARVOREB * pai_atual = ler_no(files.file_indices, pos_pai);
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    int pos_filho_pai;
    int pos_pai_do_pai;
    int pos_nova_raiz;
    int no_livre;

    while( pai_atual->num_chaves < MIN && !eh_raiz(files, pai_atual)){
        pos_pai_do_pai = buscar_pai(files, pos_raiz, pai_atual->chave[0], &pos_filho_pai);

        verificar_redistribuicao_ou_concatenacao(files, pos_raiz, pai_atual, pos_pai_do_pai, pos_filho_pai, pos_pai, pai_atual->chave[0]);
        pai_atual = ler_no(files.file_indices, pos_pai_do_pai);

        if(pai_atual->num_chaves == 0){
            break;
        }
    }

    if(pai_atual->num_chaves == 0 && eh_raiz(files, pai_atual)){
        printf("\n---> entrou aquii\n");
        pos_nova_raiz = pai_atual->filho[0];
        no_livre = pai_atual->filho[1];

        cab_indices->pos_raiz = pos_nova_raiz;
        escreve_cabecalho_indices(files.file_indices, cab_indices);
        atualizar_pos_livres_indices(files, pos_pai_do_pai);
        atualizar_pos_livres_indices(files, no_livre);
    }

    free(cab_indices);
    free(pai_atual);
}

int equal(ARVOREB * raiz, ARVOREB * no_a_remover){
    if(raiz->num_chaves != no_a_remover->num_chaves) return 0;

    for(int i = 0; i < raiz->num_chaves; i++){
        if(raiz->chave[i] != no_a_remover->chave[i]) return 0;
    }

    return 1;
}

int eh_raiz(ARQUIVOS files, ARVOREB * no_a_remover){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
    ARVOREB * raiz = ler_no(files.file_indices, cab_indices->pos_raiz);

    if(equal(raiz, no_a_remover)){
        return 1;
    }

    free(raiz);
    free(cab_indices);
    return 0;
}

void remover(ARQUIVOS files, int codigo, int pos_raiz, int pos_remocao){
    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);

    // Buscar o nó que possui a chave a ser removida a ser removido
    ARVOREB * no_a_remover = ler_no(files.file_indices, pos_remocao);

    // 1° CASO: a remoção é feita em um nó folha com número de chaves maior que o mínimo (ORDEM/2)
    if( mais_chaves_que_min(no_a_remover) && eh_folha(no_a_remover) ){
        // Logo, apenas remove a chave do nó, realizando as alterações necessárias e gravando novamente no arquivo
        printf("\n--->Entrou aqui 1\n");
        remover_caso1(files, no_a_remover, codigo, pos_remocao);

    } else if ( !eh_folha(no_a_remover) ) { // CASO 2°: a remoção é feita em um nó interno
        // Logo, busca-se a chave sucessora e a insere no lugar da chave removida no nó interno
        // Além disso, a função deve retornar a posição do nó chave sucessora, pois esse nó deve ser tratado após remoção
        printf("\n--->Entrou aqui 2\n");
        int pos_no_sucessor = remover_caso2(files, no_a_remover, codigo, pos_remocao);
        ARVOREB * no_sucessor = ler_no(files.file_indices, pos_no_sucessor);
        int pos_filho_remocao;

        int pos_pai;
        printf("\n---> CODIGO para procurar pai apos remocao caso 2: %d\n", no_sucessor->chave[0]);
        if(no_sucessor->num_chaves != 0)
            pos_pai = buscar_pai(files, pos_remocao, no_sucessor->chave[0], &pos_filho_remocao);
        else{
            pos_pai = pos_remocao;
            pos_filho_remocao = pos_no_sucessor;
        }

        if(no_sucessor->num_chaves < MIN) {
            verificar_redistribuicao_ou_concatenacao(files, pos_raiz, no_sucessor, pos_pai, pos_filho_remocao,
                                                     pos_no_sucessor, no_sucessor->chave[0]);
            remover_caso4(files, cab_indices->pos_raiz, pos_pai);
        }
        imprimir_cabecalho_indices(cab_indices);

    } else if ( !mais_chaves_que_min(no_a_remover) && eh_folha(no_a_remover) ){
        // CASO 3°: a remoção é feita em um nó com numero minimo de chaves
        // Logo, é necessário verificar, PRIMEIRAMENTE, se pode ser feito a redistribuição
        // Caso contrário, fazer concatenação

        printf("\n--->Entrou aqui CASO 3\n");
        // Busca o pai para poder veirificar os filhos irmão e verificar se podem emprestar
        int pos_filho_remocao;
        int pos_pai = buscar_pai(files, cab_indices->pos_raiz, codigo, &pos_filho_remocao);
        printf("\n  ----> POS PAI: %d\n", pos_pai);
        printf("\n  ----> POS filho remocao: %d\n", pos_filho_remocao);

        remover_caso1(files, no_a_remover, codigo, pos_remocao);

        if(eh_raiz(files, no_a_remover) && no_a_remover->num_chaves == 0){ // Logo, a raiz ficou vazia
            cab_indices->pos_raiz = -1;
            cab_indices->pos_livre = -1;
            escreve_cabecalho_indices(files.file_indices, cab_indices);
            return;
        }

        verificar_redistribuicao_ou_concatenacao(files, pos_raiz, no_a_remover, pos_pai, pos_filho_remocao, pos_remocao, codigo);
        printf("\n---> Chamando caso 4!\n");
        remover_caso4(files, cab_indices->pos_raiz, pos_pai);
        imprimir_cabecalho_indices(cab_indices);
    }

    printf("\n---> Remocao realizada com sucesso!\n");

    free(cab_indices);
}