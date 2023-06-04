#include "kdtree.h"
#include <stdlib.h>

void montarArvore(kdtree *arv, int k, int (*comparador)(const void *a, const void *b, int k)) {
    (*arv).raiz = NULL;
    (*arv).k = k;
    (*arv).comparador = comparador;
}

void inserirItem(kdtree *arv, treg *item) {
    //Só deve ser chamada após montarArvore e inserirPontosMedios
    tnode **pNode = &(*arv).raiz;
    tnode **nodePai = NULL;
    int profundidade = 0;
    while ((*pNode) != NULL) {
        nodePai = pNode;
        int kCompara = profundidade % (*arv).k;
        if ((*arv).comparador((**pNode).val->coord, item->coord, kCompara) >= 0) {
            pNode = &(**pNode).e;
        } else {
            pNode = &(**pNode).d;
        }
        profundidade++;
    }
    tnode *novo = (tnode *) malloc(sizeof(tnode));
    (*novo).pai = nodePai!= NULL ? (*nodePai) : NULL;
    (*novo).e = NULL;
    (*novo).d = NULL;
    (*novo).val = item;
    *pNode = novo;
}

int partitionPontos(treg **pontos, int inicio, int fim, int k, int (*comparador)(const void *a, const void *b, int k)) {
    void *pivot = pontos[fim]->coord;
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        if (comparador(pontos[j]->coord, pivot, k) < 0) {
            treg *aux;
            aux = pontos[i];
            pontos[i] = pontos[j];
            pontos[j] = aux;
            i++;
        }
    }
    treg *aux = pontos[i];
    pontos[i] = pontos[fim];
    pontos[fim] = aux;
    return i;
}

void
ordenarPontosPorD(treg **pontos, int inicio, int fim, int k, int (*comparador)(const void *a, const void *b, int k)) {
    if (fim > inicio) {
        int indicePivo = partitionPontos(pontos, inicio, fim, k, comparador);
        ordenarPontosPorD(pontos, inicio, indicePivo - 1, k, comparador);
        ordenarPontosPorD(pontos, indicePivo + 1, fim, k, comparador);
    }
}

tnode *inserirPontosMediosRaiz(treg **pontos, int inicio, int fim, int k, int maxK, tnode* pai,
                               int (*comparador)(const void *a, const void *b, int k)) {
    tnode *nodeRes = (tnode *) malloc(sizeof(tnode));
    if (inicio == fim) {
        (*nodeRes).val = pontos[fim];
        (*nodeRes).pai = pai;
        (*nodeRes).d = NULL;
        (*nodeRes).e = NULL;
        return nodeRes;
    }
    ordenarPontosPorD(pontos, inicio, fim, k, comparador);
    int mediana = (fim + inicio) / 2;
    (*nodeRes).val = pontos[mediana];
    (*nodeRes).pai = pai;
    (*nodeRes).e = inserirPontosMediosRaiz(pontos, inicio, mediana - 1, (k + 1) % maxK, maxK,nodeRes, comparador);
    (*nodeRes).d = inserirPontosMediosRaiz(pontos, mediana + 1, fim, (k + 1) % maxK, maxK,nodeRes, comparador);
    return nodeRes;
}

/**
* Deve ser o método utilizado para fazer a inserção dos nós
* na árvore após sua montagem. Isso pois garante que a árvore
* esteja balanceada - ou seja, as operações de pesquisa pelo(s) nó(s)
* mais próximo(s) serão mais eficientes ( complexidade O(log n) ).
**/
void
inserirPontosMedios(kdtree *arv, treg **pontos, int qtdPontos, int (*comparador)(const void *a, const void *b, int k)) {
    (*arv).raiz = inserirPontosMediosRaiz(pontos, 0, qtdPontos - 1, 0, (*arv).k, NULL, comparador);
}

double calcularDistancia(void *a, void *b, int kMax, int (*comparador)(const void *a, const void *b, int k)) {
    double distancia = 0.0;
    for (int k = 0; k < kMax; k++) {
        double diff = comparador(a, b, k);
        distancia += diff * diff;
    }
    return distancia;
}

void encontrarMaisProximo(tnode *node, void *ponto, int kMax, int profundidade, tnode **pontoMaisProx,
                          double *menorDistancia, int (*comparador)(const void *a, const void *b, int k)) {
    if (node == NULL) {
        return;
    }

    double distancia = calcularDistancia(node->val->coord, ponto, kMax, comparador);

    if (distancia < *menorDistancia || *menorDistancia < 0) {
        *menorDistancia = distancia;
        *pontoMaisProx = node;
    }

    int k = profundidade % kMax;
    int comparacao = comparador(ponto, node->val->coord, k);

    if (comparacao < 0) {
        encontrarMaisProximo(node->e, ponto, kMax, profundidade + 1, pontoMaisProx, menorDistancia, comparador);
        if (comparacao * comparacao < *menorDistancia) {
            encontrarMaisProximo(node->d, ponto, kMax, profundidade + 1, pontoMaisProx, menorDistancia, comparador);
        }
    } else {
        encontrarMaisProximo(node->d, ponto, kMax, profundidade + 1, pontoMaisProx, menorDistancia, comparador);
        if (comparacao * comparacao < *menorDistancia) {
            encontrarMaisProximo(node->e, ponto, kMax, profundidade + 1, pontoMaisProx, menorDistancia, comparador);
        }
    }
}

tnode *acharPontoMaisProx(kdtree *arv, void *ponto) {
    tnode *pontoMaisProx = NULL;
    double menorDistancia = -1;
    encontrarMaisProximo((*arv).raiz, ponto, (*arv).k, 0, &pontoMaisProx, &menorDistancia, (*arv).comparador);

    return pontoMaisProx;
}

tnode* sucessor(tnode* node){
    if(node == NULL) return NULL;
    
    tnode* pNode = node;
    if(pNode->d != NULL){
        pNode = pNode->d;
        while (pNode->e != NULL){
            pNode = pNode->e;
        }
        return pNode;
    }else{
        while(pNode->pai != NULL){
            if(pNode == pNode->pai->d){
                pNode = pNode->pai;
            }
            else{
                return pNode->pai;
            }
        }
    }
    return NULL;
}

tnode* antecessor(tnode* node){
    if(node == NULL) return NULL;
    
    tnode* pNode = node;
    if(pNode->e != NULL){
        pNode = pNode->e;
        while (pNode->d != NULL){
            pNode = pNode->d;
        }
        return pNode;
    }else{
        while(pNode->pai != NULL){
            if(pNode == pNode->pai->e){
                pNode = pNode->pai;
            }
            else{
                return pNode->pai;
            }
        }
    }
    return NULL;
}