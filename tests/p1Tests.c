//
// Created by diogo on 04/06/2023.
//
#include "../problema1/problema1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../libKdTree/kdtree.h"
void testarPontos(){

    kdtree arvMunicipios = montarArvoreMunicipios();
    ponto pontoDesejado = {-20.4486,-54.6295};
    municipio* res = municipioMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->nomeMunicipio, "Campo Grande") == 0);
    assert(strcmp(res->codigoUf, "MS") == 0);

    pontoDesejado.lat = -27.6126;
    pontoDesejado.lon = -51.0233;
    res = municipioMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->nomeMunicipio, "Abdon Batista") == 0);
    assert(strcmp(res->codigoUf, "SC") == 0);

    pontoDesejado.lat = -1.41412;
    pontoDesejado.lon = -51.6338;
    res = municipioMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->nomeMunicipio, "Gurupá") == 0);
    assert(strcmp(res->codigoUf, "PA") == 0);

    pontoDesejado.lat = -14.2711;
    pontoDesejado.lon = -42.257;
    res = municipioMaisProximo(pontoDesejado,&arvMunicipios);
    assert(strcmp(res->nomeMunicipio, "Ibiassucê") == 0);
    assert(strcmp(res->codigoUf, "BA") == 0);
}

int main(){
    testarPontos();
    return EXIT_SUCCESS;
}