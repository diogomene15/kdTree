//
// Created by diogo on 04/06/2023.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    FILE* arquivoMunicipios = fopen("municipios.csv", "r");
    if(arquivoMunicipios == NULL){
        printf("Arquivo nao encontrado!!");
    }
    return EXIT_SUCCESS;
}