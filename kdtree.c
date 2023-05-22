#include "kdtree.h"
#include <stdlib.h>

void montarArvore(kdtree* arv, int k, int (*comparador)(const void* a, const void *b)){
    (*arv).raiz = NULL;
    (*arv).k = k;
    (*arv).comparador = comparador;
}

void inserirItem(kdtree* arv, void* item){
    tnode **pNode = &(*arv).raiz;
    int profundidade = 0;
    while((*pNode) != NULL){
        int kCompara = profundidade % (*arv).k;
        if( (*arv).comparador((**pNode).val+kCompara, item+kCompara) >= 0 ){
            pNode = &(**pNode).e;
        }
        else{
            pNode = &(**pNode).d;
        }
        profundidade++;
    }
    tnode* novo = (tnode*) malloc(sizeof(tnode));
    (*novo).e = NULL;
    (*novo).d = NULL;
    (*novo).val = item;
    *pNode = novo;
}

int partitionPontos(void** pontos, int inicio, int fim, int k, int (*comparador)(const void* a, const void *b)){
    void* pivot = pontos[fim]+k;
    int i = inicio;
    for(int j=inicio; j<fim; j++){
        if(comparador(pontos[j]+k,pivot) < 0){
            void* aux;
            aux = pontos[i];
            pontos[i] = pontos[j];
            pontos[j]= aux;
            i++;
        }
    }
    void* aux = pontos[i];
    pontos[i] = pontos[fim];
    pontos[fim] = aux;
    return i;
}
void ordenarPontosPorD(void** pontos, int inicio, int fim, int k, int (*comparador)(const void* a, const void *b)){
    if(fim > inicio){
        int indicePivo = partitionPontos(pontos, inicio, fim, k, comparador);
        ordenarPontosPorD(pontos, inicio, indicePivo-1, k, comparador);
        ordenarPontosPorD(pontos, indicePivo+1, fim, k, comparador);
    }
}
 tnode* inserirPontosMediosRaiz(void** pontos, int inicio, int fim, int k, int maxK, int (*comparador)(const void* a, const void *b)){
     tnode* nodeRes = (tnode*) malloc(sizeof(tnode));
     if(inicio==fim){
         (*nodeRes).val = pontos[fim];
         (*nodeRes).d = NULL;
         (*nodeRes).e = NULL;
         return  nodeRes;
     }
     ordenarPontosPorD(pontos, inicio, fim, k, comparador);
     int mediana = (fim+inicio)/2;
     (*nodeRes).val = pontos[mediana];
     (*nodeRes).e = inserirPontosMediosRaiz(pontos, inicio, mediana-1, (k+1)% maxK, maxK,comparador);
     (*nodeRes).d = inserirPontosMediosRaiz(pontos, mediana+1, fim, (k+1)% maxK, maxK,comparador);
     return nodeRes;
 }
 void inserirPontosMedios(kdtree * arv, void** pontos, int qtdPontos, int (*comparador)(const void* a, const void *b)){
     (*arv).raiz = inserirPontosMediosRaiz(pontos, 0, qtdPontos-1, 0, (*arv).k, comparador);
}

// void acharMaisProx(kdtree* arv, void* ponto){

// }
