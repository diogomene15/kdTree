//
// Created by diogo on 05/06/2023.
//
#include "problema2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int contaLinhas(const char* nomeArquivo){
    int totalLinhas = 0;
    FILE* arquivo = fopen(nomeArquivo, "r");
    char ch;
    while (feof(arquivo)==0) {
        ch = fgetc(arquivo);
        if (ch == '\n') {
            totalLinhas++;
        }
    }
    return totalLinhas;
}
void lerRestaurante(restaurante *** listaRestaurantes, int* numRestaurantes){
    FILE* arquivoRestaurante = fopen("./Fast_Food_Restaurants_US.csv", "r");
    if(arquivoRestaurante == NULL){
        printf("Arquivo de restaurantes nao encontrado!!");
        return;
    }
    int linhasArquivo = contaLinhas("./Fast_Food_Restaurants_US.csv");
    (*listaRestaurantes) = (restaurante**) malloc(linhasArquivo* sizeof(restaurante*));
    fscanf(arquivoRestaurante, "%*[^\n]");
    int contador = 0;
    while(feof(arquivoRestaurante)==0){
        restaurante * novoRestaurante = (restaurante *) malloc(sizeof(restaurante));
        int temp;
        fscanf(arquivoRestaurante, "%d,",&temp);
        fscanf(arquivoRestaurante,"%[^,]",novoRestaurante->address);
        fscanf(arquivoRestaurante,",%[^,\"]",novoRestaurante->categories);
        if(novoRestaurante->categories[0]=='\0'){
            fscanf(arquivoRestaurante,"\"%[^\"]%*c",novoRestaurante->categories);
        }
        fscanf(arquivoRestaurante,",%[^,]",novoRestaurante->city);
        fscanf(arquivoRestaurante,",%[^,]",novoRestaurante->country);
        fscanf(arquivoRestaurante,",%f,",&novoRestaurante->lat);
        fscanf(arquivoRestaurante,"%f,",&novoRestaurante->lon);
        fscanf(arquivoRestaurante,"%[^,\"]",novoRestaurante->name);
        if(novoRestaurante->name[0]=='\0'){
            fscanf(arquivoRestaurante,"\"%[^\"]%*c",novoRestaurante->name);
        }
        fscanf(arquivoRestaurante,",%[^,]",novoRestaurante->postalCode);
        fscanf(arquivoRestaurante,",%2s",novoRestaurante->province);
        fscanf(arquivoRestaurante,",%[^\n]",novoRestaurante->website);

        (*listaRestaurantes)[contador++] = novoRestaurante;
    }
    *numRestaurantes = contador;
}

float comparadorRestaurante(const void *a, const void *b, int k) {
    float a1 = 0;
    float b1 = 0;
    if (k == 0) {
        a1 = ((restaurante *) a)->lat + 90;
        b1 = ((restaurante *) b)->lat + 90;
    } else {
        a1 = ((restaurante *) a)->lon + 180;
        b1 = ((restaurante *) b)->lon + 180;
    }
    return a1 - b1;
}
kdtree montarArvoreRestaurantes(){
    int contRestautantes;
    restaurante** restaurantes;

    lerRestaurante(&restaurantes, &contRestautantes);
    kdtree arvore;
    int k = 2;
    montarArvore(&arvore, k, comparadorRestaurante);
    inserirPontosMedios(&arvore, (void**) restaurantes, contRestautantes);
    return arvore;
}

restaurante* restauranteMaisProximo(ponto pontoR, kdtree* arvore){
    restaurante ponto;
    ponto.lat = pontoR.lat;
    ponto.lon = pontoR.lon;

    tnode* pontoMaisProx = acharPontoMaisProx(arvore, &ponto);
    return (restaurante*) (pontoMaisProx->val);
}