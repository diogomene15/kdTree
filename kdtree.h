#ifndef KDTREE_H
#define KDTREE_H

typedef struct node{
    void *val;
    struct node* d;
    struct node* e;
}tnode;

typedef struct kdtree{
    tnode *raiz;
    int k; //Resolvi não fixar as dimensões da árvore para duas
    int (*comparador)(void* a, void* b, int k);
}kdtree;

#endif //KDTREE_H
