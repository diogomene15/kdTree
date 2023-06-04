//
// Created by diogo on 04/06/2023.
//

#ifndef PROBLEMA1_H
#define PROBLEMA1_H
#define TAM_COD_IBGE 8
#define TAM_NOME_MUNICIPIO 40
#define TAM_CODIGO_UF 3
#define TAM_UF_ESTADO 30
#define TAM_REGIAO 20
#define TAM_COD_SIAFI 5
#define TAM_FUSO_HORARIO 30
typedef struct regMunicipio{
    int lat;
    int lon;
    char codIBGE[TAM_COD_IBGE];
    char codSIAFI[TAM_COD_SIAFI];
    char nomeMunicipio[TAM_NOME_MUNICIPIO];
    int capital;
    char codigo_uf[TAM_CODIGO_UF];
    char uf_estado[TAM_UF_ESTADO];
    char regiao[TAM_REGIAO];
    int ddd;
    char fusoHorario[TAM_FUSO_HORARIO];
} municipio;

typedef struct regEstado{
    int codigo_uf;
    char uf_estado[TAM_UF_ESTADO];
    char regiao[TAM_REGIAO];
}estado;

#endif //PROBLEMA1_H
