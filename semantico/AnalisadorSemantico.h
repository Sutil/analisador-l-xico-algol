//
// Created by sutil on 14/01/17.
//

#ifndef PROJETOU_ANALISADORSEMANTICO_H
#define PROJETOU_ANALISADORSEMANTICO_H

#include "../sintatico/No.h"

struct registro {
    string chave;
    string valor;
};
typedef struct registro Registro;

struct tabela {
    vector<registro*> registros;
};
typedef struct tabela Tabela;

struct escopo {
    int chave;
    tabela * tab;

    escopo(int chave){
        this->chave = chave;
    }
};
typedef struct escopo Escopo;

bool aliseSemantica(No * raiz);

#endif //PROJETOU_ANALISADORSEMANTICO_H
