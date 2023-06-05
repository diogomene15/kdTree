//
// Created by diogo on 04/06/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problema1.h"
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
void lerEstados(estado** listaEstados, int* numEstados){
    FILE* arquivoEstados = fopen("./estados.csv", "r");
    if(arquivoEstados == NULL){
        printf("Arquivo de estados nao encontrado!!");
        return;
    }
    int linhasArquivo = contaLinhas("./estados.csv");
    *numEstados = linhasArquivo;
    (*listaEstados) = (estado*) malloc(linhasArquivo* sizeof(estado));
    fscanf(arquivoEstados, "%*[^\n]");

    int contador = 0;
    while(feof(arquivoEstados)==0){
        int numUf;
        char codigoUf[TAM_CODIGO_UF];
        char ufEstado[TAM_UF_ESTADO];
        char regiao[TAM_REGIAO];
        //11,RO,Rondônia,-10.83,-63.34,Norte
        fscanf(arquivoEstados, "%d", &numUf);
        fscanf(arquivoEstados,",%2s",codigoUf);
        fscanf(arquivoEstados,",%[^,]",ufEstado);
        fscanf(arquivoEstados,",%*[^,]");
        fscanf(arquivoEstados,",%*[^,]");
        fscanf(arquivoEstados,",%[^\n]",regiao);
        estado novoEstado;
        novoEstado.numUf = numUf;
        strcpy(novoEstado.codigoUf,codigoUf);
        strcpy(novoEstado.ufEstado,ufEstado);
        strcpy(novoEstado.regiao, regiao);
        *((*listaEstados)+contador) = novoEstado;
        contador++;
    }
}
estado findEstado(int numUf, estado* estados, int tamanhoVetor) {
    for (int i = 0; i < tamanhoVetor; i++) {
        if (estados[i].numUf == numUf) {
            return estados[i];
        }
    }
}


void lerMunicipio(municipio*** listaMunicipios, int* numMunicipios){

    int numEstados;
    estado* estados;
    lerEstados(&estados, &numEstados);

    FILE* arquivoEstados = fopen("./municipios.csv", "r");
    if(arquivoEstados == NULL){
        printf("Arquivo de estados nao encontrado!!");
        return;
    }
    int linhasArquivo = contaLinhas("./municipios.csv");
    *numMunicipios = linhasArquivo;
    (*listaMunicipios) = (municipio**) malloc(linhasArquivo* sizeof(municipio*));
    fscanf(arquivoEstados, "%*[^\n]");

    int contador = 0;
    while(feof(arquivoEstados)==0){
        float lat;
        float lon;
        char codIBGE[TAM_COD_IBGE];
        char codSIAFI[TAM_COD_SIAFI];
        char nomeMunicipio[TAM_NOME_MUNICIPIO];
        int capital;
        int numUf;
        int ddd;
        char fusoHorario[TAM_FUSO_HORARIO];
        //11,RO,Rondônia,-10.83,-63.34,Norte
        fscanf(arquivoEstados, "%7s", codIBGE);
        fscanf(arquivoEstados,",%[^,]",nomeMunicipio);
        fscanf(arquivoEstados,",%f",&lat);
        fscanf(arquivoEstados,",%f",&lon);
        fscanf(arquivoEstados,",%d",&capital);
        fscanf(arquivoEstados,",%d",&numUf);
        fscanf(arquivoEstados,",%4s",codSIAFI);
        fscanf(arquivoEstados,",%d",&ddd);
        fscanf(arquivoEstados,",%[^\n]",fusoHorario);

        municipio* novoMunicipio = (municipio*) malloc(sizeof(municipio));
        novoMunicipio->lat = lat;
        novoMunicipio->lon = lon;
        strcpy(novoMunicipio->codIBGE,codIBGE);
        strcpy(novoMunicipio->codSIAFI,codSIAFI);
        strcpy(novoMunicipio->nomeMunicipio,nomeMunicipio);
        novoMunicipio->capital = capital;
        novoMunicipio->numUf = numUf;
        estado estadoMuni = findEstado(numUf, estados, numEstados);
        strcpy(novoMunicipio->codigoUf,estadoMuni.codigoUf);
        strcpy(novoMunicipio->ufEstado,estadoMuni.ufEstado);
        strcpy(novoMunicipio->regiao,estadoMuni.regiao);
        novoMunicipio->ddd = ddd;
        strcpy(novoMunicipio->fusoHorario,fusoHorario);
        (*listaMunicipios)[contador] = novoMunicipio;
        contador++;
    }

}
float comparadorMunicipios(const void *a, const void *b, int k) {
    //comparador de inteiros
    float a1 = 0;
    float b1 = 0;
    if (k == 0) {
        a1 = ((municipio *) a)->lat + 90;
        b1 = ((municipio *) b)->lat + 90;
    } else {
        a1 = ((municipio *) a)->lon + 180;
        b1 = ((municipio *) b)->lon + 180;
    }
    return a1 - b1;
}

kdtree montarArvoreMunicipios(){
    int numMunicipios;
    municipio** municipios;

    lerMunicipio(&municipios, &numMunicipios);
    kdtree arvore;
    int k = 2;

    montarArvore(&arvore, k, comparadorMunicipios);
    inserirPontosMedios(&arvore, (void**) municipios, numMunicipios);
    return arvore;
}
municipio* municipioMaisProximo(ponto pontoR, kdtree* arvore){
    municipio ponto;
    ponto.lat = pontoR.lat;
    ponto.lon = pontoR.lon;

    tnode* pontoMaisProx = acharPontoMaisProx(arvore, &ponto);
    return (municipio*) (pontoMaisProx->val);
}