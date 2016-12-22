//
// Created by sutil on 16/12/16.
//

#include <gtest/gtest.h>
#include "../../lexico/definidorToken.h"

TEST(DefinidorToken, valorNaoENumero){
    ASSERT_FALSE(isNumero("a"));
}

TEST(DefinidorToken, valorENumero){
    ASSERT_TRUE(isNumero("1"));
}

TEST(DefinidorToken, valorCom2DigitosENumero){
    ASSERT_TRUE(isNumero("1"));
}

TEST(DefinidorToken, valorDoTipoNumerico){
    ASSERT_EQ("NUM", getTipoToken("10"));
}

TEST(DefinidorToken, valorSemTipoDefinido){
    ASSERT_EQ("NADA", getTipoToken("1A"));
}

TEST(DefinidorToken, valorTipoVariavel){
    ASSERT_EQ("TIPO", getTipoToken("int"));
}

TEST(DefinidorToken, identificador){
    ASSERT_EQ("ID", getTipoToken("saldo"));
}

TEST(DefinidorToken, simboloDeAtribuicao){
    ASSERT_EQ("SIMBOLO", getTipoToken(":="));
}

TEST(DefinidorToken, simboloDeMais){
    ASSERT_EQ("SIMBOLO", getTipoToken("+"));
}

TEST(DefinidorToken, operadorRelacional){
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("<"));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("<="));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("=="));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken(">"));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken(">="));
}