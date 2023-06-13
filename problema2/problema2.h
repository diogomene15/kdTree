//
// Created by diogo on 05/06/2023.
//

#ifndef KDTREE_PROBLEMA2_H
#define KDTREE_PROBLEMA2_H
#include "../libKdTree/kdtree.h"
typedef struct rest{
    char address[100];
    char categories[255];
    char city[100];
    char country[3];
    float lat;
    float lon;
    char name[100];
    char postalCode[6];
    char province[3];
    char website[1500];
}restaurante;

typedef struct ponto{
    float lat;
    float lon;
}ponto;
kdtree montarArvoreRestaurantes();
restaurante* restauranteMaisProximo(ponto pontoR, kdtree* arvore);
#endif //KDTREE_PROBLEMA2_H
