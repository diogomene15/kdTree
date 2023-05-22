#ifndef KDTREE_H
#define KDTREE_H

typedef struct node{
    void *val;
    struct node* d;
    struct node* e;
}tnode;

typedef struct kdtree{
    tnode *raiz;
    int k; //Resolvi não fixar as dimensões da árvore
    int (*comparador)(const void* a, const void* b, int k);
}kdtree;

void montarArvore(kdtree* arv, int k, int (*comparador)(const void* a, const void *b, int k));
void inserirItem(kdtree* arv, void* item);
void inserirPontosMedios(kdtree * arv, void** pontos, int qtdPontos, int (*comparador)(const void* a, const void *b, int k));
tnode* acharPontoMaisProx(kdtree* arv, void* ponto);
#endif //KDTREE_H
