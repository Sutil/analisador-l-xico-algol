//
// Created by sutil on 16/12/16.
//

#include <gtest/gtest.h>
#include "../../lexico/definidorToken.h"

TEST(DefinidorToken, valorNaoEhNumero){
    ASSERT_FALSE(isNumero("a"));
}

TEST(DefinidorToken, valorEhNumero){
    ASSERT_TRUE(isNumero("1"));
}

TEST(DefinidorToken, valorCom2DigitosEhNumero){
    ASSERT_TRUE(isNumero("13"));
}

TEST(DefinidorToken, valorDoTipoNumerico){
    ASSERT_EQ("NUM", getTipoToken("10"));
    ASSERT_EQ("NUM", getTipoToken("10.2"));
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
    ASSERT_EQ("identifier", getTipoToken("saldo"));
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

TEST(DefinidorToken, separators){
    ASSERT_EQ("separator", getTipoToken(","));
    ASSERT_EQ("separator", getTipoToken("."));
    ASSERT_EQ("separator", getTipoToken(":"));
    ASSERT_EQ("separator", getTipoToken(";"));
    ASSERT_EQ("separator", getTipoToken(":="));
    ASSERT_EQ("separator", getTipoToken("_"));
    ASSERT_EQ("separator", getTipoToken("step"));
    ASSERT_EQ("separator", getTipoToken("until"));
    ASSERT_EQ("separator", getTipoToken("while"));
    ASSERT_EQ("separator", getTipoToken("comment"));
}

TEST(DefinidoToken, sequentialOperator){
    ASSERT_EQ("sequential operator", getTipoToken("goto"));
    ASSERT_EQ("sequential operator", getTipoToken("if"));
    ASSERT_EQ("sequential operator", getTipoToken("then"));
    ASSERT_EQ("sequential operator", getTipoToken("else"));
    ASSERT_EQ("sequential operator", getTipoToken("for"));
    ASSERT_EQ("sequential operator", getTipoToken("do"));
}

TEST(DefinidorToken, strings){
    ASSERT_EQ("string", getTipoToken("\"uma string\""));
}
