//
// Created by sutil on 14/01/17.
//

#ifndef PROJETOU_ANALISADORSEMANTICO_H
#define PROJETOU_ANALISADORSEMANTICO_H

#include "../sintatico/No.h"

struct registro {
    string chave;
    string valor;

    registro(string chave, string valor){
        this->chave = chave;
        this->valor = valor;
    }
};
typedef struct registro Registro;

struct tabela {
    int escopo;
    vector<registro*> registros;

    tabela(int escopo){
        this->escopo = escopo;
    }
};
typedef struct tabela Tabela;


bool aliseSemantica(No * raiz);

#endif //PROJETOU_ANALISADORSEMANTICO_H
