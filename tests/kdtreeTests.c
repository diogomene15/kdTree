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

    treg p1; int p1c[] = {1,2}; p1.coord = p1c;
    treg p2; int p2c[] = {3,4}; p2.coord = p2c;
    treg p3; int p3c[] = {4,5}; p3.coord = p3c;
    treg p4; int p4c[] = {0, 0}; p4.coord = p4c;
    treg p5; int p5c[] = {0,10}; p5.coord = p5c;
    inserirItem(arv, &p1);
    inserirItem(arv, &p2);
    inserirItem(arv, &p3);
    inserirItem(arv, &p1);
    inserirItem(arv, &p4);
    inserirItem(arv, &p1);
    inserirItem(arv, &p5);

    assert(arv->raiz->val->coord == (void*)p1c);
    assert(arv->raiz->pai == NULL);

    assert(arv->raiz->d->val->coord == (void*)p2c);
    assert(arv->raiz->d->pai == arv->raiz);

    assert(arv->raiz->d->d->val->coord == (void*)p3c);
    assert(arv->raiz->d->d->pai == arv->raiz->d);

    assert(arv->raiz->e->val->coord == (void*)p1c);
    assert(arv->raiz->e->pai == arv->raiz);

    assert(arv->raiz->e->e->val->coord == (void*)p4c);
    assert(arv->raiz->e->e->pai == arv->raiz->e);

    assert(arv->raiz->e->e->d->val->coord == (void*)p1c);
    assert(arv->raiz->e->e->d->pai == arv->raiz->e->e);

    assert(arv->raiz->e->d->val->coord == (void*)p5c);
    assert(arv->raiz->e->d->pai == arv->raiz->e);
    free(arv);
}

void testeInsercaoPontos(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int c1[] = {4,5}; treg p1; p1.coord = c1;
    int c2[] = {1,4}; treg p2; p2.coord = c2;
    int c3[] = {7,4}; treg p3; p3.coord = c3;
    int c4[] = {-2,4}; treg p4; p4.coord = c4;
    int c5[] = {-4,2}; treg p5; p5.coord = c5;
    int c6[] = {8,6}; treg p6; p6.coord = c6;
    int c7[] = {9,2}; treg p7; p7.coord = c7;

    treg** pontos = (treg **) malloc(7*sizeof(int*));
    pontos[0] = &p2;
    pontos[1] = &p1;
    pontos[2] = &p3;
    pontos[3] = &p4;
    pontos[4] = &p5;
    pontos[5] = &p6;
    pontos[6] = &p7;
    inserirPontosMedios(arv,(treg **)pontos, 7, comparador);
    assert((arv->raiz->val) == &p1);
    assert((arv->raiz->e->val) == &p2);
    assert((arv->raiz->e->d->val) == &p4);
    assert((arv->raiz->e->e->val) == &p5);

    assert((arv->raiz->d->val) == &p3);
    assert((arv->raiz->d->d->val) == &p6);
    assert((arv->raiz->d->e->val) == &p7);
    free(pontos);

    pontos = calloc(1, sizeof(int*));
    pontos[0] = &p2;
    inserirPontosMedios(arv,(treg **)pontos, 1, comparador);
    assert(arv->raiz->val == &p2);
    free(pontos);
    free(arv);
}
void testeAcharMaisProx(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int c1[] = {4,5}; treg p1; p1.coord = c1;
    int c2[] = {1,4}; treg p2; p2.coord = c2;
    int c3[] = {7,4}; treg p3; p3.coord = c3;
    int c4[] = {-2,4}; treg p4; p4.coord = c4;
    int c5[] = {-4,2}; treg p5; p5.coord = c5;
    int c6[] = {8,6}; treg p6; p6.coord = c6;
    int c7[] = {9,2}; treg p7; p7.coord = c7;

    treg ** pontos = (treg **) malloc(7*sizeof(int*));
    pontos[0] = &p2;
    pontos[1] = &p1;
    pontos[2] = &p3;
    pontos[3] = &p4;
    pontos[4] = &p5;
    pontos[5] = &p6;
    pontos[6] = &p7;
    inserirPontosMedios(arv,(treg **)pontos, 7, comparador);

    int pontoPesquisa[] = {10,2};
    tnode* res = acharPontoMaisProx(arv, pontoPesquisa);
    assert(res->val == &p7);

    int pontoPesquisa2[] = {7,5};
    res = acharPontoMaisProx(arv, pontoPesquisa2);
    assert(res->val == &p3);

    int pontoPesquisa3[] = {4,1};
    res = acharPontoMaisProx(arv, pontoPesquisa3);
    assert(res->val == &p1);
    free(pontos);
    free(arv);
}
void testaSucessor(){
    kdtree* arv = (kdtree*) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int c1[] = {1,2}; treg p1; p1.coord = c1;
    int c2[] = {3,4}; treg p2; p2.coord = c2;
    int c3[] = {4,5}; treg p3; p3.coord = c3;
    int c4[] = {0, 0}; treg p4; p4.coord = c4;
    int c5[] = {0,10}; treg p5; p5.coord = c5;

    inserirItem(arv, &p1);
    inserirItem(arv, &p2);
    inserirItem(arv, &p3);
    inserirItem(arv, &p1);
    inserirItem(arv, &p4);
    inserirItem(arv, &p1);
    inserirItem(arv, &p5);

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

    int c1[] = {1,2}; treg p1; p1.coord = c1;
    int c2[] = {3,4}; treg p2; p2.coord = c2;
    int c3[] = {4,5}; treg p3; p3.coord = c3;
    int c4[] = {0, 0}; treg p4; p4.coord = c4;
    int c5[] = {0,10}; treg p5; p5.coord = c5;

    inserirItem(arv, &p1);
    inserirItem(arv, &p2);
    inserirItem(arv, &p3);
    inserirItem(arv, &p1);
    inserirItem(arv, &p4);
    inserirItem(arv, &p1);
    inserirItem(arv, &p5);

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

