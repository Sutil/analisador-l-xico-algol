//
// Created by sutil on 03/01/17.
//

#include <gtest/gtest.h>
#include "../../sintatico/No.h"

TEST(arvore, no){
    No * raiz = new No("raiz");


    No * a1 = new No("a1");
    No * a2 = new No("a2");

    raiz->addFilho(a1);
    raiz->addFilho(a2);

    No * b1 = new No("b1");
    No * b2 = new No("b2");

    a1->addFilho(b1);
    a2->addFilho(b2);


    raiz->imprimir();
}
