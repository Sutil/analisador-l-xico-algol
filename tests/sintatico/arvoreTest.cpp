//
// Created by sutil on 03/01/17.
//

#include <gtest/gtest.h>
#include "../../sintatico/No.h"

TEST(arvore, no){
    No * raiz = new No("raiz");


    No * a1 = new No("a1");
    No * a2 = new No("a2");

    adicionaFilho(raiz, raiz, a1);
    adicionaFilho(raiz, raiz, a2);

    No * b1 = new No("b1");
    No * b2 = new No("b2");

    adicionaFilho(raiz, a1, b1);
    adicionaFilho(raiz, a2, b2);

    raiz->imprimir();
}
