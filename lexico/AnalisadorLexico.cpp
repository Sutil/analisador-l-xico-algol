//
// Created by sutil on 16/12/16.
//

#include "AnalisadorLexico.h"
#include "separador.h"
#include "definidorToken.h"

FILE *file;
int linhaAtual  = 1;
int linhaARetornar =  0;
int colunaAtual =  0;
int colunaARetornar = 0;

string definineTipoToken(string basic_string);

void inicializaAnalizadorLexico(FILE *pFile) {
    file = pFile;
    linhaAtual  = 1;
    linhaARetornar =  0;
    colunaAtual =  0;
    colunaARetornar = 0;
}

void incrementaLinhaColuna(char caracter){
    if(caracter == '\n'){
        linhaAtual++;
        colunaAtual = 1;
    } else
        colunaAtual++;
}

char leCaracter(){
    char caracter = fgetc(file);
    incrementaLinhaColuna(caracter);
    return caracter;
}

string leValorToken(){
    char caracter = leCaracter();
    colunaARetornar = colunaAtual;
    linhaARetornar = linhaAtual;

    char sequencia[50];
    int i = 0;

    while(!isSeparadorDescartavel(caracter)){
        sequencia[i] = caracter;
        caracter = leCaracter();
        i++;
    }
    sequencia[i] = '\0';

    string valorToken(sequencia);
    return valorToken;
}

string definineTipoToken(string valorToken) {
    string tipoToken = getTipoToken(valorToken);
    return tipoToken;
}

Token * getToken() {

    string valorToken = leValorToken();
    string tipoToken = definineTipoToken(valorToken);

    Token * token = new Token(valorToken, tipoToken, linhaARetornar, colunaARetornar);

    return token;
}
