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
    FILE * f = criaArquivo("integer");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("integer", "declarator", 1, 1, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, atribuicao){
    FILE * f = criaArquivo("integer saldo := 0;");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("integer", "declarator", 1, 1, token);

    token = getToken();
    assertToken("saldo", "identifier", 1, 9, token);

    token = getToken();
    assertToken(":=", "separator", 1, 15, token);

    token = getToken();
    assertToken("0", "NUM", 1, 18, token);

    token = getToken();
    assertToken(";", "separator", 1, 19, token);

    token = getToken();
    assertToken("EOF", "EOF", 2, 1, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, ignoraEspacosEmBranco){
    FILE * f = criaArquivo("a +  10  ");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("a", "identifier", 1, 1, token);

    token = getToken();
    assertToken("+", "arithmetic operator", 1, 3, token);

    token = getToken();
    assertToken("10", "NUM", 1, 6, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, declaracaoProcedure){
    FILE * f = criaArquivo("procedure multiMatriz(a, b)");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("procedure", "declarator", 1, 1, token);

    token = getToken();
    assertToken("multiMatriz", "identifier", 1, 11, token);

    token = getToken();
    assertToken("(", "bracket", 1, 22, token);

    token = getToken();
    assertToken("a", "identifier", 1, 23, token);

    token = getToken();
    assertToken(",", "separator", 1, 24, token);

    token = getToken();
    assertToken("b", "identifier", 1, 26, token);

    token = getToken();
    assertToken(")", "bracket", 1, 27, token);

    fclose(f);
    remove("test.txt");
}

/*
 * procedure multiMatriz(a, b, n, m)
    value n, m; array a, b, y; integer n, m;
begin
    integer i, j, k, somatorio, produto;
    i := k := j = 0;

    for i := 1 step 1 until n do
        for q := 1 step 1 until m do
        begin
            somatorio := 0;
            for k:= 1 step 1 until m
                begin
                    produto := a[i,k] * b[k, j];
                    somatorio := somatorio + produto;
                end
            r[i, j] := somatorio;
        end


end multiMatriz
 */

//criar um teste para fazer toda a análse deste programa.