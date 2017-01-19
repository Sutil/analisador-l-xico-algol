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

    registro * copy(){
        return new registro(this->chave, this->valor);
    }
};
typedef struct registro Registro;

struct tabela {
    int escopo;
    vector<Registro*> registros;

    tabela(int escopo){
        this->escopo = escopo;
    }

    void addRegistro(Registro * registro){
        this->registros.push_back(registro);
    }

    tabela * copy(int escopo){
        tabela * t = new tabela(escopo);
        for(registro * r : this->registros)
            t->addRegistro(r->copy());

        return t;
    }

    bool variavelEstaNaTabela(string variavel){
        for(Registro * r : registros)
            if(r->valor.compare(variavel) == 0)
                return true;

        return false;
    }

    string getTipoVariavel(string nomeVariavel){
        for(Registro * r : registros)
            if(r->valor.compare(nomeVariavel) == 0)
                return r->chave;

        return "";
    }
};
typedef struct tabela Tabela;


bool aliseSemantica(No * raiz);

#endif //PROJETOU_ANALISADORSEMANTICO_H
