//
// Created by sutil on 20/12/16.
//

#include "leitorValorToken.h"
#include "separador.h"

int linha = 0;
int coluna = 0;
int colunaARetorno = 0;
char caracter;


char leCaracter(FILE* file){
    caracter  = getc(file);
    if(caracter == '\n') {
        linha++;
        coluna = 0;
    }
    else
        coluna++;

    return caracter;
}

void salvaColuna(){
    colunaARetorno = coluna;
}

void voltaPonteiro(FILE * file){
    fseek(file, 0, file->_offset);
    fseek(file, -1, SEEK_CUR);
    if(caracter == '\n')
        linha--;
    else
        coluna--;
}

void descartarCaracteresEmBranco(FILE  * file){
    char caracter = leCaracter(file);
    if(isSeparadorDescartavel(caracter))
        while(isSeparadorDescartavel(caracter))
            caracter = leCaracter(file);

    if(EOF != caracter)
        voltaPonteiro(file);
    else
        coluna--;
}

string tokenEOF(FILE * file){
    char caracter = leCaracter(file);
    salvaColuna();
    if(caracter == EOF)
        return "EOF";

    voltaPonteiro(file);
    return "";
}

string tokenQueContemSeparador(FILE * file){
    char caracter = leCaracter(file);
    salvaColuna();
    if(isSeparadorComSequencia(caracter)) {
        char sequencia[3];
        sequencia[0] = caracter;
        sequencia[1] = leCaracter(file);
        sequencia[2] = '\0';
        string valor(sequencia);
        return valor;
    }
    voltaPonteiro(file);
    return "";
}

string tokenSimbolo(FILE * file){
    char caracter = leCaracter(file);
    salvaColuna();
    if(isSeparadorNaoDescartavel(caracter)){
        char sequencia[2];
        sequencia[0] = caracter;
        sequencia[1] = '\0';
        string valor(sequencia);
        return valor;
    }
    voltaPonteiro(file);
    return "";
}

string tokenSemSimbolo(FILE * file){
    char caracter = leCaracter(file);
    salvaColuna();
    char sequencia[50];
    int i = 0;
    while (!isSeparador(caracter)){
        sequencia[i] = caracter;
        i++;
        caracter = leCaracter(file);
    }
    sequencia[i] = '\0';
    voltaPonteiro(file);
    string valor(sequencia);
    return valor;
}

ValorToken* getValorToken(FILE * file, int linhaAtual, int colunaAtual){
    linha = linhaAtual;
    coluna = colunaAtual;

    descartarCaracteresEmBranco(file);

    string valor = tokenEOF(file);

    if(valor.empty())
        valor = tokenQueContemSeparador(file);

    if(valor.empty())
        valor = tokenSimbolo(file);

    if(valor.empty())
        valor = tokenSemSimbolo(file);

    return new ValorToken(valor, linha, coluna, colunaARetorno);
}



