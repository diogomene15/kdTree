#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
 int comparador(const void* a, const void* b){
     //comparador de inteiros
     int a1 = *((int*) a);
     int b1 = *((int*) b);
     return a1 - b1;
 }
int main() {
    kdtree* arv = (kdtree*) malloc(sizeof(arv));
    montarArvore(arv, 2, comparador);

    int p1[] = {1,2};
    int p2[] = {3,4};
    int p3[] = {4,5};
    int p4[] = {0, 0};

    inserirItem(arv, p1);
    inserirItem(arv, p2);
    inserirItem(arv, p3);
    inserirItem(arv, p1);
    inserirItem(arv, p4);
    inserirItem(arv, p1);

    return EXIT_SUCCESS;
}
