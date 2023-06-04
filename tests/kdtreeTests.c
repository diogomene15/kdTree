#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../libKdTree/kdtree.h"

int comparador(const void *a, const void *b, int k) {
    //comparador de inteiros
    int a1 = ((int *) a)[k];
    int b1 = ((int *) b)[k];
    return a1 - b1;
}

typedef struct coord {
    char dummy;
    int lat;
    int lon;
} coord;

int comparadorObjeto(const void *a, const void *b, int k) {
    //comparador de inteiros
    int a1 = 0;
    int b1 = 0;
    if (k == 0) {
        a1 = ((coord *) a)->lat;
        b1 = ((coord *) b)->lat;
    } else {
        a1 = ((coord *) a)->lon;
        b1 = ((coord *) b)->lon;
    }
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

void testeInsercaoItem() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1, 2};
    int p2[] = {3, 4};
    int p3[] = {4, 5};
    int p4[] = {0, 0};
    int p5[] = {0, 10};

    inserirItem(arv, p1);
    inserirItem(arv, p2);
    inserirItem(arv, p3);
    inserirItem(arv, p1);
    inserirItem(arv, p4);
    inserirItem(arv, p1);
    inserirItem(arv, p5);

    assert(arv->raiz->val == (void *) p1);
    assert(arv->raiz->pai == NULL);

    assert(arv->raiz->d->val == (void *) p2);
    assert(arv->raiz->d->pai == arv->raiz);

    assert(arv->raiz->d->d->val == (void *) p3);
    assert(arv->raiz->d->d->pai == arv->raiz->d);

    assert(arv->raiz->e->val == (void *) p1);
    assert(arv->raiz->e->pai == arv->raiz);

    assert(arv->raiz->e->e->val == (void *) p4);
    assert(arv->raiz->e->e->pai == arv->raiz->e);

    assert(arv->raiz->e->e->d->val == (void *) p1);
    assert(arv->raiz->e->e->d->pai == arv->raiz->e->e);

    assert(arv->raiz->e->d->val == (void *) p5);
    assert(arv->raiz->e->d->pai == arv->raiz->e);
    free(arv);
}
void testeInsercaoItemCoord() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparadorObjeto);

    coord p1; p1.dummy = 'a'; p1.lat= 1; p1.lon = 2;
    coord p2; p2.dummy = 'a'; p2.lat= 3; p2.lon = 4;
    coord p3; p3.dummy = 'a'; p3.lat= 4; p3.lon = 5;
    coord p4; p4.dummy = 'a'; p4.lat= 0; p4.lon = 0;
    coord p5; p5.dummy = 'a'; p5.lat= 0; p5.lon = 1;

    inserirItem(arv, &p1);
    inserirItem(arv, &p2);
    inserirItem(arv, &p3);
    inserirItem(arv, &p1);
    inserirItem(arv, &p4);
    inserirItem(arv, &p1);
    inserirItem(arv, &p5);

    assert(arv->raiz->val == (void *) &p1);
    assert(arv->raiz->pai == NULL);

    assert(arv->raiz->d->val == (void *) &p2);
    assert(arv->raiz->d->pai == arv->raiz);

    assert(arv->raiz->d->d->val == (void *) &p3);
    assert(arv->raiz->d->d->pai == arv->raiz->d);

    assert(arv->raiz->e->val == (void *) &p1);
    assert(arv->raiz->e->pai == arv->raiz);

    assert(arv->raiz->e->e->val == (void *) &p4);
    assert(arv->raiz->e->e->pai == arv->raiz->e);

    assert(arv->raiz->e->e->d->val == (void *) &p1);
    assert(arv->raiz->e->e->d->pai == arv->raiz->e->e);

    assert(arv->raiz->e->e->e->val == (void *) &p5);
    assert(arv->raiz->e->e->pai == arv->raiz->e);
    free(arv);
}


void testeInsercaoPontos() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {4, 5};
    int p2[] = {1, 4};
    int p3[] = {7, 4};
    int p4[] = {-2, 4};
    int p5[] = {-4, 2};
    int p6[] = {8, 6};
    int p7[] = {9, 2};

    int **pontos = (int **) malloc(7 * sizeof(int *));
    pontos[0] = p2;
    pontos[1] = p1;
    pontos[2] = p3;
    pontos[3] = p4;
    pontos[4] = p5;
    pontos[5] = p6;
    pontos[6] = p7;
    inserirPontosMedios(arv, (void **) pontos, 7);
    assert(arv->raiz->val == p1);
    assert(arv->raiz->e->val == p2);
    assert(arv->raiz->e->d->val == p4);
    assert(arv->raiz->e->e->val == p5);

    assert(arv->raiz->d->val == p3);
    assert(arv->raiz->d->d->val == p6);
    assert(arv->raiz->d->e->val == p7);
    free(pontos);

    pontos = calloc(1, sizeof(int *));
    pontos[0] = p2;
    inserirPontosMedios(arv, (void **) pontos, 1);
    assert(arv->raiz->val == p2);
    free(pontos);
    free(arv);
}

void testeAcharMaisProx() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {4, 5};
    int p2[] = {1, 4};
    int p3[] = {7, 4};
    int p4[] = {-2, 4};
    int p5[] = {-4, 2};
    int p6[] = {8, 6};
    int p7[] = {9, 2};

    int **pontos = (int **) malloc(7 * sizeof(int *));
    pontos[0] = p2;
    pontos[1] = p1;
    pontos[2] = p3;
    pontos[3] = p4;
    pontos[4] = p5;
    pontos[5] = p6;
    pontos[6] = p7;
    inserirPontosMedios(arv, (void **) pontos, 7);

    int pontoPesquisa[] = {10, 2};
    tnode *res = acharPontoMaisProx(arv, pontoPesquisa);
    assert(res->val == p7);

    int pontoPesquisa2[] = {7, 5};
    res = acharPontoMaisProx(arv, pontoPesquisa2);
    assert(res->val == p3);

    int pontoPesquisa3[] = {4, 1};
    res = acharPontoMaisProx(arv, pontoPesquisa3);
    assert(res->val == p1);
    free(pontos);
    free(arv);
}

void testeAcharMaisProxCoord() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparadorObjeto);

    coord p1; p1.dummy = 'a'; p1.lat =4; p1.lon = 5;
    coord p2; p2.dummy = 'a'; p2.lat =1; p2.lon = 4;
    coord p3; p3.dummy = 'a'; p3.lat =7; p3.lon = 4;
    coord p4; p4.dummy = 'a'; p4.lat =-2; p4.lon = 4;
    coord p5; p5.dummy = 'a'; p5.lat =-4; p5.lon = 2;
    coord p6; p6.dummy = 'a'; p6.lat =8; p6.lon = 6;
    coord p7; p7.dummy = 'a'; p7.lat =9; p7.lon = 2;

    coord **pontos = (coord **) malloc(7 * sizeof(coord*));
    pontos[0] = &p2;
    pontos[1] = &p1;
    pontos[2] = &p3;
    pontos[3] = &p4;
    pontos[4] = &p5;
    pontos[5] = &p6;
    pontos[6] = &p7;
    inserirPontosMedios(arv, (void **) pontos, 7);

    coord pontoPesquisa;
    pontoPesquisa.dummy = 'a';
    pontoPesquisa.lat = 10;
    pontoPesquisa.lon =2;
    tnode *res = acharPontoMaisProx(arv, &pontoPesquisa);
    assert((*(coord *)res->val).lat == p7.lat);
    assert((*(coord *)res->val).lon == p7.lon);

    coord pontoPesquisa2;
    pontoPesquisa2.dummy = 'a';
    pontoPesquisa2.lat = 7;
    pontoPesquisa2.lon =5;
    res = acharPontoMaisProx(arv, &pontoPesquisa2);
    assert((*(coord *)res->val).lat == p3.lat);
    assert((*(coord *)res->val).lon == p3.lon);

    coord pontoPesquisa3;
    pontoPesquisa3.dummy = 'a';
    pontoPesquisa3.lat = 4;
    pontoPesquisa3.lon =1;
    res = acharPontoMaisProx(arv, &pontoPesquisa3);
    assert((*(coord *)res->val).lat == p1.lat);
    assert((*(coord *)res->val).lon == p1.lon);
    free(pontos);
    free(arv);
}

void testaSucessor() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1, 2};
    int p2[] = {3, 4};
    int p3[] = {4, 5};
    int p4[] = {0, 0};
    int p5[] = {0, 10};

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

void testaAntecessor() {
    kdtree *arv = (kdtree *) malloc(sizeof(kdtree));
    montarArvore(arv, 2, comparador);

    int p1[] = {1, 2};
    int p2[] = {3, 4};
    int p3[] = {4, 5};
    int p4[] = {0, 0};
    int p5[] = {0, 10};

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

int main() {
    testeMontarArvore();
    testeInsercaoItem();
    testeInsercaoItemCoord();
    testeInsercaoPontos();
    testeAcharMaisProx();
    testeAcharMaisProxCoord();
    testaSucessor();
    testaAntecessor();
    return EXIT_SUCCESS;
}

