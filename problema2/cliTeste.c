//
// Created by diogo on 13/06/2023.
//
#include "../problema2/problema2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparTela(){
    #ifdef _WIN32 //Deve atender a maior parte dos PC's :)
        system("cls");
    #else
        system("clear");
    #endif
}

void pause(){
    #ifdef _WIN32 //Deve atender a maior parte dos PC's :)
        system("pause");
    #else
        system("read -p \"Pressione enter para continuar...\" saindo");
    #endif
}

void buscarPonto(kdtree* arvMunicipios){

    limparTela();
    float lat, lon;
    printf("Latitude: ");
    scanf("%f", &lat);
    printf("Longitude: ");
    scanf("%f", &lon);

    
    ponto pontoDesejado = {lat,lon};
    restaurante * res = restauranteMaisProximo(pontoDesejado,arvMunicipios);
    printf("\nNome: %s\n",res->name);
    printf("Endereco: %s\n",res->address);
    printf("Cidade: %s\n",res->city);
    printf("Estado: %s\n",res->province);
    printf("Pais: %s\n",res->country);
    printf("CEP: %s\n",res->postalCode);
    printf("Latitude: %f\n",res->lat);
    printf("Longitude: %f\n",res->lon);
    printf("Categorias: %s\n",res->categories);
    printf("Website: %s\n",res->website);
    printf("\n\n");
    pause();
    limparTela();
}
void freeTree(tnode* raiz){
    if(raiz != NULL){
        freeTree(raiz->e);
        freeTree(raiz->d);
        free(raiz->val);
        free(raiz);
    }
}
int main(void){
    kdtree arvMunicipios = montarArvoreRestaurantes();
    int option = -1;
    while(option != 0){
        printf("Escolha uma opcao:\n(0)Sair\n(1)Buscar restaurante mais proximo\n>");
        scanf("%d",&option);
        if(option == 1){
            buscarPonto(&arvMunicipios);
        }
    }
    freeTree(arvMunicipios.raiz);
    return EXIT_SUCCESS;
}