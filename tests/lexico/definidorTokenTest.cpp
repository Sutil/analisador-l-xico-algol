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
    ASSERT_EQ("declarator", getTipoToken("integer"));
}

TEST(DefinidorToken, ownDeclarator){
    ASSERT_EQ("declarator", getTipoToken("own"));
}

TEST(DefinidorToken, boolenaDeclarator){
    ASSERT_EQ("declarator", getTipoToken("boolean"));
}

TEST(DefinidorToken, realDeclarator){
    ASSERT_EQ("declarator", getTipoToken("real"));
}

TEST(DefinidorToken, arrayDeclarator){
    ASSERT_EQ("declarator", getTipoToken("array"));
}

TEST(DefinidorToken, switchDeclarator){
    ASSERT_EQ("declarator", getTipoToken("switch"));
}

TEST(DefinidorToken, procedureDeclarator){
    ASSERT_EQ("declarator", getTipoToken("procedure"));
}

TEST(DefinidorToken, specificator){
    ASSERT_EQ("specificator", getTipoToken("string"));
    ASSERT_EQ("specificator", getTipoToken("label"));
    ASSERT_EQ("specificator", getTipoToken("value"));
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

TEST(DefinidorToken, bracket){
    ASSERT_EQ("bracket", getTipoToken("("));
    ASSERT_EQ("bracket", getTipoToken(")"));
    ASSERT_EQ("bracket", getTipoToken("["));
    ASSERT_EQ("bracket", getTipoToken("]"));
    ASSERT_EQ("bracket", getTipoToken("`"));
    ASSERT_EQ("bracket", getTipoToken("'"));
    ASSERT_EQ("bracket", getTipoToken("begin"));
    ASSERT_EQ("bracket", getTipoToken("end"));
}

TEST(DefinidorToken, operadorRelacional){
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("<"));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("<="));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken("=="));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken(">"));
    ASSERT_EQ("RELATIONAL_OPERATOR", getTipoToken(">="));
}