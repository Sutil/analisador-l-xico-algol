//
// Created by sutil on 20/12/16.
//

#ifndef PROJETOU_LEITORVALORTOKEN_H
#define PROJETOU_LEITORVALORTOKEN_H

#include <string>
#include "separador.h"

using namespace std;

struct valorToken{
    string valor;
    int linha;
    int colunaAtual;
    int colunaARetornar;

    valorToken(string valor, int linha, int coluna, int colunaARetornar){
        this->valor = valor;
        this->linha = linha;
        this->colunaAtual = coluna;
        this->colunaARetornar = colunaARetornar;
    }
};

typedef struct valorToken ValorToken;

ValorToken* getValorToken(FILE * file, int linhaAtual, int colunaAtual);

#endif //PROJETOU_LEITORVALORTOKEN_H
