//
// Created by sutil on 20/12/16.
//

#include <gtest/gtest.h>
#include "../../lexico/leitorValorToken.h"
#include "abreArquivo.h"

using namespace std;

TEST(leitorValor, lerSimbolo){
    FILE * f = criaArquivo(" + ");
    ValorToken* valor = getValorToken(f);
    ASSERT_EQ("+", valor->valor);
    fechaERemove(f);
}

TEST(leitorValor, lerSimboloAtribuicao){
    FILE * f = criaArquivo(" := ");
    ValorToken* valor = getValorToken(f);
    ASSERT_EQ(":=", valor->valor);
    fechaERemove(f);
}

TEST(leitorValor, lerNumero){
    inicializaLeitorToken();
    FILE * f = criaArquivo(" 123 ");
    ValorToken* valor = getValorToken(f);
    ASSERT_EQ("123", valor->valor);
    //ASSERT_EQ(2, valor->coluna);
    ASSERT_EQ(1, valor->linha);
    fechaERemove(f);
}

TEST(leitorValor, lerVarios){
    FILE * f = criaArquivo(" 123 abc:= 1 -;");
    ValorToken* valor = getValorToken(f);
    ASSERT_EQ("123", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("abc", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ(":=", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("1", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("-", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ(";", valor->valor);
    fechaERemove(f);
}

//procedure multiMatriz(a, b) Size:(n, m) Result:(r);
TEST(leitorValor, lerCabecalhoProcedure){
    FILE * f = criaArquivo("procedure multiMatriz(a, b);");
    ValorToken* valor = getValorToken(f);
    ASSERT_EQ("procedure", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("multiMatriz", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("(", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("a", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ(",", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("b", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ(")", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ(";", valor->valor);

    valor = getValorToken(f);
    ASSERT_EQ("EOF", valor->valor);


    fechaERemove(f);
}