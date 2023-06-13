//
// Created by diogo on 13/06/2023.
//
#include "problema1.h"
#include <stdio.h>
#include <stdlib.h>

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
    municipio * res = municipioMaisProximo(pontoDesejado,arvMunicipios);
    printf("\nNome: %s\n",res->nomeMunicipio);
    printf("Codigo IBGE: %s\n",res->codIBGE);
    printf("Codigo SIAFI: %s\n",res->codSIAFI);
    printf("Capital: %s\n",res->capital ? "Sim" : "Nao");
    printf("Numero UF: %d\n",res->numUf);
    printf("Codigo UF: %s\n",res->codigoUf);
    printf("UF: %s\n",res->ufEstado);
    printf("Regiao: %s\n",res->regiao);
    printf("DDD: %d\n",res->ddd);
    printf("Fuso Horario: %s\n",res->fusoHorario);
    printf("Latitude: %f\n",res->lat);
    printf("Longitude: %f\n",res->lon);
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
    kdtree arvMunicipios = montarArvoreMunicipios();
    int option = -1;
    while(option != 0){
        printf("Escolha uma opcao:\n(0)Sair\n(1)Buscar municipio mais proximo\n>");
        scanf("%d",&option);
        if(option == 1){
            buscarPonto(&arvMunicipios);
        }
    }
    freeTree(arvMunicipios.raiz);
    return EXIT_SUCCESS;
}