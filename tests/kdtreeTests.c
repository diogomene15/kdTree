#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../kdtree.h"

int comparador(const void* a, const void* b, int k){
    //comparador de inteiros
    int a1 = ((int*) a)[k];
    int b1 = ((int*) b)[k];
    return a1 - b1;
}

void testeMontarArvore() {
    kdtree arvore;
    int k = 2;

    montarArvore(&arvore, k, comparador);

    assert(arvore.raiz == NULL);
    assert(arvore.k == k);
    assert(arvore.comparador == comparador);
}
void testeInsercaoItem(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1,2};
    int p2[] = {3,4};
    int p3[] = {4,5};
    int p4[] = {0, 0};
    int p5[] = {0,10};

    inserirItem(arv, p1);
    inserirItem(arv, p2);
    inserirItem(arv, p3);
    inserirItem(arv, p1);
    inserirItem(arv, p4);
    inserirItem(arv, p1);
    inserirItem(arv, p5);

    assert(arv->raiz->val == (void*)p1);
    assert(arv->raiz->pai == NULL);

    assert(arv->raiz->d->val == (void*)p2);
    assert(arv->raiz->d->pai == arv->raiz);

    assert(arv->raiz->d->d->val == (void*)p3);
    assert(arv->raiz->d->d->pai == arv->raiz->d);

    assert(arv->raiz->e->val == (void*)p1);
    assert(arv->raiz->e->pai == arv->raiz);

    assert(arv->raiz->e->e->val == (void*)p4);
    assert(arv->raiz->e->e->pai == arv->raiz->e);

    assert(arv->raiz->e->e->d->val == (void*)p1);
    assert(arv->raiz->e->e->d->pai == arv->raiz->e->e);

    assert(arv->raiz->e->d->val == (void*)p5);
    assert(arv->raiz->e->d->pai == arv->raiz->e);
    free(arv);
}

void testeInsercaoPontos(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {4,5};
    int p2[] = {1,4};
    int p3[] = {7,4};
    int p4[] = {-2,4};
    int p5[] = {-4,2};
    int p6[] = {8,6};
    int p7[] = {9,2};

    int** pontos = (int**) malloc(7*sizeof(int*));
    pontos[0] = p2;
    pontos[1] = p1;
    pontos[2] = p3;
    pontos[3] = p4;
    pontos[4] = p5;
    pontos[5] = p6;
    pontos[6] = p7;
    inserirPontosMedios(arv,(void**)pontos, 7, comparador);
    assert(arv->raiz->val == p1);
    assert(arv->raiz->e->val == p2);
    assert(arv->raiz->e->d->val == p4);
    assert(arv->raiz->e->e->val == p5);

    assert(arv->raiz->d->val == p3);
    assert(arv->raiz->d->d->val == p6);
    assert(arv->raiz->d->e->val == p7);
    free(pontos);

    pontos = calloc(1, sizeof(int*));
    pontos[0] = p2;
    inserirPontosMedios(arv,(void**)pontos, 1, comparador);
    assert(arv->raiz->val == p2);
    free(pontos);
    free(arv);
}

void testeAcharMaisProx(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {4,5};
    int p2[] = {1,4};
    int p3[] = {7,4};
    int p4[] = {-2,4};
    int p5[] = {-4,2};
    int p6[] = {8,6};
    int p7[] = {9,2};

    int** pontos = (int**) malloc(7*sizeof(int*));
    pontos[0] = p2;
    pontos[1] = p1;
    pontos[2] = p3;
    pontos[3] = p4;
    pontos[4] = p5;
    pontos[5] = p6;
    pontos[6] = p7;
    inserirPontosMedios(arv,(void**)pontos, 7, comparador);

    int pontoPesquisa[] = {10,2};
    tnode* res = acharPontoMaisProx(arv, pontoPesquisa);
    assert(res->val == p7);

    int pontoPesquisa2[] = {7,5};
    res = acharPontoMaisProx(arv, pontoPesquisa2);
    assert(res->val == p3);

    int pontoPesquisa3[] = {4,1};
    res = acharPontoMaisProx(arv, pontoPesquisa3);
    assert(res->val == p1);
    free(pontos);
    free(arv);
}
void testaSucessor(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1,2};
    int p2[] = {3,4};
    int p3[] = {4,5};
    int p4[] = {0, 0};
    int p5[] = {0,10};

    inserirItem(arv, p1);
    inserirItem(arv, p2);
    inserirItem(arv, p3);
    inserirItem(arv, p1);
    inserirItem(arv, p4);
    inserirItem(arv, p1);
    inserirItem(arv, p5);

    assert(sucessor(arv->raiz->e) == arv->raiz->e->d);
    assert(sucessor(arv->raiz->e->e) == arv->raiz->e->e->d);
    assert(sucessor(arv->raiz->d) == arv->raiz->d->d);
    assert(sucessor(arv->raiz->e->d) == arv->raiz);
    assert(sucessor(arv->raiz) == arv->raiz->d);

    free(arv);
}
void testaAntecessor(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1,2};
    int p2[] = {3,4};
    int p3[] = {4,5};
    int p4[] = {0, 0};
    int p5[] = {0,10};

    inserirItem(arv, p1);
    inserirItem(arv, p2);
    inserirItem(arv, p3);
    inserirItem(arv, p1);
    inserirItem(arv, p4);
    inserirItem(arv, p1);
    inserirItem(arv, p5);

    assert(antecessor(arv->raiz) == arv->raiz->e->d);
    assert(antecessor(arv->raiz->d) == arv->raiz);
    assert(antecessor(arv->raiz->d->d) == arv->raiz->d);
    assert(antecessor(arv->raiz->e->d) == arv->raiz->e);

    free(arv);
}

int main(){
    testeMontarArvore();
    testeInsercaoItem();
    testeInsercaoPontos();
    testeAcharMaisProx();
    testaSucessor();
    testaAntecessor();
    return EXIT_SUCCESS;
}

