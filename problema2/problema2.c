//
// Created by diogo on 05/06/2023.
//
#include "problema2.h"
#include <stdio.h>
#include <stdlib.h>
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
        printf("Arquivo de estados nao encontrado!!");
        return;
    }
    int linhasArquivo = contaLinhas("./municipios.csv");
    *numRestaurantes = linhasArquivo;
    (*listaRestaurantes) = (restaurante**) malloc(linhasArquivo* sizeof(restaurante*));
    fscanf(arquivoRestaurante, "%*[^\n]");

    int contador = 0;
    while(feof(arquivoRestaurante)==0){
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
        restaurante * novoRestaurante = (restaurante *) malloc(sizeof(restaurante));
        fscanf(arquivoRestaurante, "%*d");
        fscanf(arquivoRestaurante,",%[^,]",address);
        fscanf(arquivoRestaurante,",%[^,]",categories);
        fscanf(arquivoRestaurante,",%[^,]",city);
        fscanf(arquivoRestaurante,",%[^,]",country);
        fscanf(arquivoRestaurante,",%f",&lat);
        fscanf(arquivoRestaurante,",%f",&lon);
        fscanf(arquivoRestaurante,",%[^,]",name);
        fscanf(arquivoRestaurante,",%5s",postalCode);
        fscanf(arquivoRestaurante,",%2s",province);
        fscanf(arquivoRestaurante,",%[^\n]",website);


        (*listaRestaurantes)[contador] = novoRestaurante;
        contador++;
    }

}

int main(){
    restaurante** listaRestaurantes;
    int contRestautantes;

    lerRestaurante(&listaRestaurantes, &contRestautantes);
}