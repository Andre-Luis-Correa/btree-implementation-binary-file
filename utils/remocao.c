// Deleting a key from a B-tree in C

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
    int item[MAX + 1], count;
    struct BTreeNode *linker[MAX + 1];
};

struct BTreeNode *root;

// Node creation
struct BTreeNode *createNode(int item, struct BTreeNode *child) {
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->item[1] = item;
    newNode->count = 1;
    newNode->linker[0] = root;
    newNode->linker[1] = child;
    return newNode;
}

// Add value to the node
void addValToNode(int item, int pos, struct BTreeNode *node,
                  struct BTreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->item[j + 1] = node->item[j];
        node->linker[j + 1] = node->linker[j];
        j--;
    }
    node->item[j + 1] = item;
    node->linker[j + 1] = child;
    node->count++;
}

// Split the node
void splitNode(int item, int *pval, int pos, struct BTreeNode *node,
               struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->item[j - median] = node->item[j];
        (*newNode)->linker[j - median] = node->linker[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        addValToNode(item, pos, node, child);
    } else {
        addValToNode(item, pos - median, *newNode, child);
    }
    *pval = node->item[node->count];
    (*newNode)->linker[0] = node->linker[node->count];
    node->count--;
}

// Set the value in the node
int setValueInNode(int item, int *pval,
                   struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = item;
        *child = NULL;
        return 1;
    }

    if (item < node->item[1]) {
        pos = 0;
    } else {
        for (pos = node->count;
             (item < node->item[pos] && pos > 1); pos--)
            ;
        if (item == node->item[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValueInNode(item, pval, node->linker[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insertion operation
void insertion(int item) {
    int flag, i;
    struct BTreeNode *child;

    flag = setValueInNode(item, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Copy the successor
void copySuccessor(struct BTreeNode *myNode, int pos) {
    struct BTreeNode *dummy;
    dummy = myNode->linker[pos];

    for (; dummy->linker[0] != NULL;)
        dummy = dummy->linker[0];
    myNode->item[pos] = dummy->item[1];
}

// Remove the value
void removeVal(struct BTreeNode *myNode, int pos) {
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->item[i - 1] = myNode->item[i];
        myNode->linker[i - 1] = myNode->linker[i];
        i++;
    }
    myNode->count--;
}

// Do right shift
void rightShift(struct BTreeNode *myNode, int pos) {
    struct BTreeNode *x = myNode->linker[pos];
    int j = x->count;

    while (j > 0) {
        x->item[j + 1] = x->item[j];
        x->linker[j + 1] = x->linker[j];
    }
    x->item[1] = myNode->item[pos];
    x->linker[1] = x->linker[0];
    x->count++;

    x = myNode->linker[pos - 1];
    myNode->item[pos] = x->item[x->count];
    myNode->linker[pos] = x->linker[x->count];
    x->count--;
    return;
}

// Do left shift
void leftShift(struct BTreeNode *myNode, int pos) {
    int j = 1;
    struct BTreeNode *x = myNode->linker[pos - 1];

    x->count++;
    x->item[x->count] = myNode->item[pos];
    x->linker[x->count] = myNode->linker[pos]->linker[0];

    x = myNode->linker[pos];
    myNode->item[pos] = x->item[1];
    x->linker[0] = x->linker[1];
    x->count--;

    while (j <= x->count) {
        x->item[j] = x->item[j + 1];
        x->linker[j] = x->linker[j + 1];
        j++;
    }
    return;
}

// Merge the nodes
void mergeNodes(struct BTreeNode *myNode, int pos) {
    int j = 1;
    struct BTreeNode *x1 = myNode->linker[pos], *x2 = myNode->linker[pos - 1];

    x2->count++;
    x2->item[x2->count] = myNode->item[pos];
    x2->linker[x2->count] = myNode->linker[0];

    while (j <= x1->count) {
        x2->count++;
        x2->item[x2->count] = x1->item[j];
        x2->linker[x2->count] = x1->linker[j];
        j++;
    }

    j = pos;
    while (j < myNode->count) {
        myNode->item[j] = myNode->item[j + 1];
        myNode->linker[j] = myNode->linker[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}

// Adjust the node
void adjustNode(struct BTreeNode *myNode, int pos) {
    if (!pos) {
        if (myNode->linker[1]->count > MIN) {
            leftShift(myNode, 1);
        } else {
            mergeNodes(myNode, 1);
        }
    } else {
        if (myNode->count != pos) {
            if (myNode->linker[pos - 1]->count > MIN) {
                rightShift(myNode, pos);
            } else {
                if (myNode->linker[pos + 1]->count > MIN) {
                    leftShift(myNode, pos + 1);
                } else {
                    mergeNodes(myNode, pos);
                }
            }
        } else {
            if (myNode->linker[pos - 1]->count > MIN)
                rightShift(myNode, pos);
            else
                mergeNodes(myNode, pos);
        }
    }
}

// Delete a value from the node
int delValFromNode(int item, struct BTreeNode *myNode) {
    int pos, flag = 0;
    if (myNode) {

        // 1° if
        if (item < myNode->item[1]) {
            pos = 0;
            flag = 0;
        } else {
            for (pos = myNode->count; (item < myNode->item[pos] && pos > 1); pos--)
                ;
            if (item == myNode->item[pos]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }

        // 2° if
        if (flag) {
            if (myNode->linker[pos - 1]) {
                copySuccessor(myNode, pos);
                flag = delValFromNode(myNode->item[pos], myNode->linker[pos]);
                if (flag == 0) {
                    printf("Given data is not present in B-Tree\n");
                }
            } else {
                removeVal(myNode, pos);
            }
        } else {
            flag = delValFromNode(item, myNode->linker[pos]);
        }
        if (myNode->linker[pos]) {
            if (myNode->linker[pos]->count < MIN)
                adjustNode(myNode, pos);
        }
    }
    return flag;
}

// Delete operaiton
void delete (int item, struct BTreeNode *myNode) {
    struct BTreeNode *tmp;
    if (!delValFromNode(item, myNode)) {
        printf("Not present\n");
        return;
    } else {
        if (myNode->count == 0) {
            tmp = myNode;
            myNode = myNode->linker[0];
            free(tmp);
        }
    }
    root = myNode;
    return;
}

void searching(int item, int *pos, struct BTreeNode *myNode) {
    if (!myNode) {
        return;
    }

    if (item < myNode->item[1]) {
        *pos = 0;
    } else {
        for (*pos = myNode->count;
             (item < myNode->item[*pos] && *pos > 1); (*pos)--)
            ;
        if (item == myNode->item[*pos]) {
            printf("%d present in B-tree", item);
            return;
        }
    }
    searching(item, pos, myNode->linker[*pos]);
    return;
}

void traversal(struct BTreeNode *myNode) {
    int i;
    if (myNode) {
        for (i = 0; i < myNode->count; i++) {
            traversal(myNode->linker[i]);
            printf("%d ", myNode->item[i + 1]);
        }
        traversal(myNode->linker[i]);
    }
}

int main() {
    int item, ch;

    insertion(8);
    insertion(9);
    insertion(10);
    insertion(11);
    insertion(15);
    insertion(16);
    insertion(17);
    insertion(18);
    insertion(20);
    insertion(23);

    traversal(root);

    delete (23, root);
    printf("\n");
    traversal(root);
}


////////////////////
//
//void remover_produto(ARQUIVOS files){
//    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
//    int codigo, pos_codigo;
//
//    printf ("\n---> Insira o codigo a ser removido: ");
//    scanf ("%d", &codigo);
//
//    pos_codigo = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);
//
//    if(cab_indices->pos_raiz == -1){
//        printf("\n---> A arvore encontra-se vazia!\n");
//        free(cab_indices);
//        return;
//    } else if (pos_codigo == -1) {
//        printf("\n---> Produto nao encontrado na arvore!\n");
//        free(cab_indices);
//        return;
//    }
//
//    printf("\n---> Iniciando a remocao da chave %d!\n", codigo);
//
//    free(cab_indices);
//    remover_produto_file(files, codigo);
//}
//
//void remover_produto_file(ARQUIVOS files, int codigo){
//    CABECALHO_INDICES * cab_indices = le_cabecalho_indices(files.file_indices);
//    int pos_raiz = cab_indices->pos_raiz;
//
//    ARVOREB * raiz = ler_no(files.file_indices, pos_raiz);
//    imprimir_no(raiz);
//    remover_codigo_da_arvore(files, codigo, raiz, pos_raiz);
//
//    if(raiz->num_chaves == 0){
//        raiz = ler_no(files.file_indices, raiz->filho[0]);
//        pos_raiz = raiz->filho[0];
//        escreve_no(files.file_indices, raiz, pos_raiz);
//    }
//
//    cab_indices->pos_raiz = pos_raiz;
//    escreve_cabecalho_indices(files.file_indices, cab_indices);
//    escreve_no(files.file_indices, raiz, pos_raiz);
//
//    free(raiz);
//    free(cab_indices);
//}
//
//int vazio(ARVOREB * r){
//    return r->num_chaves == 0;
//}
//
//int remover_codigo_da_arvore(ARQUIVOS files, int codigo, ARVOREB * raiz, int pos_raiz){
//    int pos, flag = 0;
//
//    // 1° : tenta encontrar a chave no nó atual (raiz atual)
//    if( !vazio(raiz) ){
//        printf("\n---> Arvore nao esta vazia! ");
//
//        if(raiz->num_chaves > 1 && codigo < raiz->chave[1]) {
//            printf("\n---> A chave e menor que a chave[1] ");
//            pos = 0;
//            flag = 0;
//
//        } else {
//            printf("\n---> A chave NAO e menor que a chave[1], continua a busca");
//            for(pos = raiz->num_chaves; (codigo < raiz->chave[pos] && pos > 1); pos--)
//                ;
//
//            if(codigo == raiz->chave[pos]){
//                flag = 1;
//            } else {
//                flag = 0;
//            }
//        }
//
//        ARVOREB * filho_pos = ler_no(files.file_indices, raiz->filho[pos]);
//
//        if( flag ){
//            ARVOREB * filho = ler_no(files.file_indices, raiz->filho[pos-1]);
//
//            if( !vazio(filho) ){
//                copiar_sucessor(files, raiz, pos_raiz, pos);
//                free(filho);
//
//                flag = remover_codigo_da_arvore(files, raiz->chave[pos], filho_pos, raiz->filho[pos]);
//                if( flag == 0 ){
//                    printf("\n---> Elemento nao encontrado na arvore!");
//                }
//            } else {
//                free(filho);
//                remover_valor(files, raiz, pos_raiz, pos);
//            }
//        } else {
//            flag = remover_codigo_da_arvore(files, codigo, filho_pos, raiz->filho[pos]);
//        }
//
//        if( !vazio(filho_pos) ){
//            if(filho_pos->num_chaves < MIN){
//                ajustar_no(files, raiz, pos_raiz, pos);
//            }
//        }
//       // escreve_no(files.file_indices, filho_pos, raiz->filho[pos]);
//        //escreve_no(files.file_indices, raiz, pos_raiz);
//
//        free(filho_pos);
//    }
//
//    return flag;
//}
//
//void ajustar_no(ARQUIVOS files, ARVOREB * no, int pos_no, int pos){
//
//    if ( !pos ) {
//        ARVOREB * filho1 = ler_no(files.file_indices, no->filho[1]);
//
//        if (filho1->num_chaves > MIN) {
//            left_shift(files, no, pos_no, 1);
//        } else {
//            concatenar_nos(files, no, pos_no, 1);
//        }
//
//        free(filho1);
//
//    } else {
//        ARVOREB * filho_antecessor = ler_no(files.file_indices, no->filho[pos-1]);
//        ARVOREB * filho_sucessor = ler_no(files.file_indices, no->filho[pos+1]);
//
//        if ( no->num_chaves != pos ) {
//            if ( filho_antecessor->num_chaves > MIN ){
//                right_shift(files, no, pos_no, pos);
//            } else {
//                if( filho_sucessor->num_chaves > MIN ) {
//                    left_shift(files, no, pos_no, pos + 1);
//                } else {
//                    concatenar_nos(files, no, pos_no, pos);
//                }
//            }
//        } else {
//            if (filho_antecessor->num_chaves > MIN)
//                right_shift(files, no, pos_no, pos);
//            else
//                concatenar_nos(files, no, pos_no, pos);
//        }
//
//        free(filho_antecessor);
//        free(filho_sucessor);
//    }
//}
//
//void left_shift(ARQUIVOS files, ARVOREB * no, int pos_no, int pos){
//    int j = 1;
//    ARVOREB * x = ler_no(files.file_indices, no->filho[pos-1]);
//    ARVOREB * aux = ler_no(files.file_indices, no->filho[pos]);
//
//    x->num_chaves++;
//    x->chave[x->num_chaves] = no->chave[pos];
//    x->pt_dados[x->num_chaves] = no->pt_dados[pos];
//    x->filho[x->num_chaves] = aux->filho[0];
//
//    x = aux;
//    no->chave[pos] = x->chave[1];
//    no->pt_dados[pos] = x->pt_dados[1];
//    x->filho[0] = x->filho[1];
//    x->num_chaves--;
//
//    while( j <= x->num_chaves ){
//        x->chave[j] = x->chave[j + 1];
//        x->pt_dados[j] = x->pt_dados[j + 1];
//        x->filho[j] = x->filho[j + 1];
//        j++;
//    }
//
//    escreve_no(files.file_indices, x, no->filho[pos-1]);
//    escreve_no(files.file_indices, no, pos_no);
//
//    free(x);
//    free(aux);
//}
//
//void right_shift(ARQUIVOS files, ARVOREB * no, int pos_no, int pos){
//    ARVOREB * x = ler_no(files.file_indices, no->filho[pos]);
//    ARVOREB * aux = ler_no(files.file_indices, no->filho[pos-1]);
//    int j = x->num_chaves;
//
//    while (j > 0) {
//        x->chave[j + 1] = x->chave[j];
//        x->pt_dados[j + 1] = x->pt_dados[j];
//        x->filho[j + 1] = x->filho[j];
//        j--;
//    }
//
//    x->chave[1] = no->chave[pos];
//    x->pt_dados[1] = no->pt_dados[pos];
//    x->filho[1] = x->filho[0];
//    x->num_chaves++;
//
//    x = aux;
//
//    no->chave[pos] = x->chave[x->num_chaves];
//    no->pt_dados[pos] = x->pt_dados[x->num_chaves];
//    no->filho[pos] = x->filho[x->num_chaves];
//    x->num_chaves--;
//
//    escreve_no(files.file_indices, x, no->filho[pos]);
//    escreve_no(files.file_indices, no, pos_no);
//
//    free(x);
//    free(aux);
//}
//
//void concatenar_nos(ARQUIVOS files, ARVOREB * no, int pos_no, int pos) {
//    int j = 1;
//    ARVOREB *x1 = ler_no(files.file_indices, no->filho[pos]), *x2 = ler_no(files.file_indices, no->filho[pos] - 1);
//
//    x2->num_chaves++;
//    x2->chave[x2->num_chaves] = no->chave[pos];
//    x2->pt_dados[x2->num_chaves] = no->pt_dados[pos];
//    x2->filho[x2->num_chaves] = no->filho[0];
//
//    while (j <= x1->num_chaves) {
//        x2->num_chaves++;
//        x2->chave[x2->num_chaves] = x1->chave[j];
//        x2->pt_dados[x2->num_chaves] = x1->pt_dados[j];
//        x2->filho[x2->num_chaves] = x1->filho[j];
//        j++;
//    }
//
//    j = pos;
//
//    while (j < no->num_chaves) {
//        no->chave[j] = no->chave[j + 1];
//        no->pt_dados[j] = no->pt_dados[j + 1];
//        no->filho[j] = no->filho[j + 1];
//        j++;
//    }
//
//    no->num_chaves--;
//
//    escreve_no(files.file_indices, x1, no->filho[pos]);
//    escreve_no(files.file_indices, x2, no->filho[pos] - 1);
//    escreve_no(files.file_indices, no, pos_no);
//
//    free(x1);
//    free(x2);
//}
//
//void remover_valor(ARQUIVOS files, ARVOREB * no, int pos_no, int pos){
//    int i = pos + 1;
//
//    while (i <= no->num_chaves){
//        no->chave[i-1] = no->chave[i];
//        no->pt_dados[i-1] = no->pt_dados[i];
//        no->filho[i-1] = no->filho[i];
//        i++;
//    }
//
//    no->num_chaves--;
//
//    escreve_no(files.file_indices, no, pos_no);
//}
//
//void copiar_sucessor(ARQUIVOS files, ARVOREB * no, int pos_no, int pos) {
//    ARVOREB * aux = ler_no(files.file_indices, no->filho[pos]);
//    ARVOREB * temp;
//
//    for( ; aux->filho[0] != -1; ){
//        temp = aux;
//        aux = ler_no(files.file_indices, aux->filho[0]);
//        free(temp);
//    }
//
//    no->chave[pos] = aux->chave[1];
//    escreve_no(files.file_indices, no, pos_no);
//    free(aux);
//}
//
//
///////////////////////////// AQUIIII
////void remover_produto(ARQUIVOS files){
////    CABECALHO_INDICES *cab_indices = le_cabecalho_indices(files.file_indices);
////    int codigo;
////
////    printf ("\n---> Insira o codigo a ser removido: ");
////    scanf ("%d", &codigo);
////
////    int pos_codigo = buscar_no(files.file_indices, codigo, cab_indices->pos_raiz);
////
////    if (cab_indices->pos_raiz == -1) {
////        printf("\n---> A arvore encontra-se vazia!\n");
////        free(cab_indices);
////        return;
////    } else if (pos_codigo == -1) {
////        printf("\n---> Produto nao encontrado na arvore!\n");
////        free(cab_indices);
////        return;
////    }
////
////    printf("\n---> Iniciando a remocao da chave %d!\n", codigo);
////
////    remover_produto_file(files, codigo);
////
////    free(cab_indices);
////}
////
////int remover_codigo_da_arvore(ARQUIVOS files, int codigo, ARVOREB *raiz, int pos_raiz) {
////    if (vazio(raiz)) {
////        printf("\n---> Arvore esta vazia!\n");
////        return 0;
////    }
////
////    int pos = buscar_chave(raiz, codigo);
////    if (pos == -1) {
////        printf("\n---> Produto nao encontrado na arvore!\n");
////        return 0;
////    }
////
////    printf("\n---> Removendo a chave %d...\n", codigo);
////    int sucesso = remover_codigo_da_arvore_recursivo(files, codigo, raiz, pos_raiz, pos);
////    if (sucesso) {
////        printf("\n---> Chave %d removida com sucesso!\n", codigo);
////    } else {
////        printf("\n---> Falha ao remover_lote a chave %d!\n", codigo);
////    }
////
////    return sucesso;
////}
////
////int remover_codigo_da_arvore_recursivo(ARQUIVOS files, int codigo, ARVOREB *no, int pos_no, int pos) {
////    int sucesso;
////
////    if (no->filho[0] == -1) {
////        // Se o nó for uma folha, remova o valor do nó
////        remover_valor(files, no, pos_no, pos);
////        sucesso = 1;
////    } else {
////        // Encontre o nó sucessor e copie seu valor para o nó atual
////        copiar_sucessor(files, no, pos_no, pos);
////        // Remova a chave duplicada no nó sucessor
////        sucesso = remover_codigo_da_arvore_recursivo(files, codigo, ler_no(files.file_indices, no->filho[pos + 1]), no->filho[pos + 1], 1);
////    }
////
////    // Verifique se o nó precisa ser ajustado após a remoção
////    if (!sucesso) {
////        printf("\n---> Falha ao remover_lote a chave %d!\n", codigo);
////        return 0;
////    }
////
////    // Verifique se o nó precisa ser ajustado após a remoção
////    if (no->num_chaves < MIN) {
////        ajustar_no(files, no, pos_no, pos);
////    }
////
////    return 1;
////}
////
////void ajustar_no(ARQUIVOS files, ARVOREB *no, int pos_no, int pos) {
////    if (pos == 0) {
////        // Se a posição for 0, ajuste o nó à esquerda
////        ARVOREB *filho_direito = ler_no(files.file_indices, no->filho[1]);
////        if (filho_direito->num_chaves > MIN) {
////            // Se o filho direito tiver chaves suficientes, faça um deslocamento à esquerda
////            left_shift(files, no, pos_no, pos + 1);
////        } else {
////            // Caso contrário, concatene os nós
////            concatenar_nos(files, no, pos_no, pos + 1);
////        }
////        free(filho_direito);
////    } else {
////        // Se a posição não for 0, ajuste o nó à direita
////        ARVOREB *filho_esquerdo = ler_no(files.file_indices, no->filho[pos - 1]);
////        if (filho_esquerdo->num_chaves > MIN) {
////            // Se o filho esquerdo tiver chaves suficientes, faça um deslocamento à direita
////            right_shift(files, no, pos_no, pos);
////        } else {
////            // Caso contrário, verifique se o próximo nó tem chaves suficientes
////            ARVOREB *proximo_filho = ler_no(files.file_indices, no->filho[pos + 1]);
////            if (proximo_filho->num_chaves > MIN) {
////                // Se o próximo filho tiver chaves suficientes, faça um deslocamento à esquerda
////                left_shift(files, no, pos_no, pos + 1);
////            } else {
////                // Caso contrário, concatene os nós
////                concatenar_nos(files, no, pos_no, pos);
////            }
////            free(proximo_filho);
////        }
////        free(filho_esquerdo);
////    }
////}
////
////void concatenar_nos(ARQUIVOS files, ARVOREB *no, int pos_no, int pos) {
////    // Implementação da concatenação de nós após a remoção
////}
////
////void remover_valor(ARQUIVOS files, ARVOREB *no, int pos_no, int pos) {
////    // Implementação da remoção de um valor do nó
////}
////
////void copiar_sucessor(ARQUIVOS files, ARVOREB *no, int pos_no, int pos) {
////    // Implementação da cópia do sucessor antes da remoção
////}
////
////void remover_produto_file(ARQUIVOS files, int codigo) {
////    // Implementação da remoção do produto no arquivo de índices
////}
////
////
////
