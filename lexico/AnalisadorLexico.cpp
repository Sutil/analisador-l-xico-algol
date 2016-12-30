//
// Created by sutil on 16/12/16.
//

#include "AnalisadorLexico.h"
#include "separador.h"
#include "definidorToken.h"
#include "leitorValorToken.h"

FILE *file;
int linhaAtual  = 1;
int colunaAtual =  0;
int colunaARetornar = 0;

string definineTipoToken(string basic_string);

bool naoEhSeparador(char caracter);

void inicializaAnalizadorLexico(FILE *pFile) {
    file = pFile;
    linhaAtual  = 1;
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

ValorToken* leValorToken(){
    ValorToken * valorToken = getValorToken(file, linhaAtual, colunaAtual);
    linhaAtual = valorToken->linha;
    colunaAtual = valorToken->colunaAtual;
    colunaARetornar = valorToken->colunaARetornar;
    return valorToken;
}

string definineTipoToken(string valorToken) {
    string tipoToken = getTipoToken(valorToken);
    return tipoToken;
}

Token * getToken() {

    ValorToken* valorToken = leValorToken();
    string tipoToken = definineTipoToken(valorToken->valor);

    Token * token = new Token(valorToken->valor, tipoToken, linhaAtual, colunaARetornar);

    return token;
}

long retornaPonteiroAtual(){
    return ftell(file);
}

void restauraPonteiro(int posicao){
    fseek(file, posicao, SEEK_SET);
}