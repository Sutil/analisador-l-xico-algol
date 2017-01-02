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
    int coluna;

    valorToken(string valor, int linha, int coluna){
        this->valor = valor;
        this->linha = linha;
        this->coluna = coluna;
    }
};

typedef struct valorToken ValorToken;

void inicializaLeitorToken();

ValorToken* getValorToken(FILE * file);

void restaurarContagem(long ponteiroArquivo);

void salvarContagem(long ponteiro);

#endif //PROJETOU_LEITORVALORTOKEN_H
