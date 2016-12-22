//
// Created by sutil on 16/12/16.
//


#include <gtest/gtest.h>

#include <fstream>
#include "../../lexico/AnalisadorLexico.h"
#include "abreArquivo.h"

using namespace std;


void assertToken(string valor, string nome, int linha, int coluna, Token* token){
    ASSERT_EQ(valor, token->valor);
    ASSERT_EQ(nome, token->nome);
    ASSERT_EQ(linha, token->linha);
    ASSERT_EQ(coluna, token->coluna);
}

TEST(Lexico, tipoVariavelValido){
    FILE * f = criaArquivo("int");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("int", "TIPO", 1, 1, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, atribuicao){
    FILE * f = criaArquivo("int saldo := 0;");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("int", "TIPO", 1, 1, token);

    token = getToken();
    assertToken("saldo", "ID", 1, 5, token);

    token = getToken();
    assertToken(":=", "SIMBOLO", 1, 11, token);

    token = getToken();
    assertToken("0", "NUM", 1, 14, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, ignoraEspacosEmBranco){
    FILE * f = criaArquivo("a +  10  ");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("a", "ID", 1, 1, token);

    token = getToken();
    assertToken("+", "SIMBOLO", 1, 3, token);

    token = getToken();
    assertToken("10", "NUM", 1, 6, token);

    fclose(f);
    remove("test.txt");
}