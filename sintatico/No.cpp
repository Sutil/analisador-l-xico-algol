//
// Created by sutil on 03/01/17.
//

#include "No.h"



bool adicionaFilho(No * raiz, No * pai, No * filho){
    if(pai->nome.compare(raiz->nome) == 0) {
        raiz->addFilho(filho);
        return true;
    }

    for(No &f : raiz->filhos) {
        if(adicionaFilho(&f, pai, filho))
            return true;
    }
    return false;
}
