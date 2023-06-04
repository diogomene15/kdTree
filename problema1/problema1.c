//
// Created by diogo on 04/06/2023.
//
#include <stdio.h>
#include <stdlib.h>
void lerMunicipos(){

}
void lerEstados(){
    FILE* arquivoMunicipios = fopen("estados.csv", "r");
    if(arquivoMunicipios == NULL){
        printf("Arquivo de estados nao encontrado!!");
    }


}
int main(int argc, char** argv){
    FILE* arquivoMunicipios = fopen("municipios.csv", "r");
    if(arquivoMunicipios == NULL){
        printf("Arquivo nao encontrado!!");
    }
    return EXIT_SUCCESS;
}