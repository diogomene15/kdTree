#include "kdtree.h"
#include <stdlib.h>

void montarArvore(kdtree* arv, int k, int (*comparador)(void* a, void *b, int k)){
    (*arv).raiz = NULL;
    (*arv).k = k;
    (*arv).comparador = comparador;
}

void inserirItem(kdtree* arv, void* item){
    int profundidade = 0;
    tnode **pNode = &(*arv).raiz;
    while((*pNode) != NULL){
        profundidade++;
        int kCompara = profundidade % (*arv).k - 1;
        if( (*arv).comparador((**pNode).val, item, kCompara) == 0 ){
            pNode = &(**pNode).e;
        }
        else{
            pNode = &(**pNode).d;
        }
    }
    tnode* novo = (tnode*) malloc(sizeof(tnode));
    (*novo).e = NULL;
    (*novo).d = NULL;
    (*novo).val = item;
    *pNode = novo;
}
