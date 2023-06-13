//
// Created by diogo on 13/06/2023.
//
//
// Created by diogo on 04/06/2023.
//
#include "../problema2/problema2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../libKdTree/kdtree.h"
void testarPontos(){

    kdtree arvMunicipios = montarArvoreRestaurantes();
    ponto pontoDesejado = {34.18063,-119.16498};
    restaurante * res = restauranteMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->name, "McDonald's") == 0);
    assert(res->lat == pontoDesejado.lat);
    assert(res->lon == pontoDesejado.lon);

    pontoDesejado.lat = 39.86891;
    pontoDesejado.lon = -84.29297;
    res = restauranteMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->name, "Taco Bell") == 0);
    assert(res->lat == pontoDesejado.lat);
    assert(res->lon == pontoDesejado.lon);

    pontoDesejado.lat = 39.347;
    pontoDesejado.lon = -84.2692;
    res = restauranteMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->name, "Subway") == 0);
    assert(res->lat == pontoDesejado.lat);
    assert(res->lon == pontoDesejado.lon);

    pontoDesejado.lat = 35.1302;
    pontoDesejado.lon = -106.53072;
    res = restauranteMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->name, "SONIC Drive In") == 0);
    assert(res->lat == pontoDesejado.lat);
    assert(res->lon == pontoDesejado.lon);

}

int main(){
    testarPontos();
    return EXIT_SUCCESS;
}