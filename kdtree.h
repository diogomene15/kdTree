#ifndef KDTREE_H
#define KDTREE_H

typedef struct node{
    void *val;
    struct node* dir;
    struct node* esq;
}node;

typedef struct kdtree{
    node *raiz;
    int k;
    int (*compara)(void* a, void* b, int k);
};

#endif //KDTREE_H
